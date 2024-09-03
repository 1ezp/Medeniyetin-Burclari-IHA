from pymavlink import mavutil
import time
from data import IHA, CAMERA, Target
from threading import Thread, Lock

# Global flags and lock
isPID = False
isTargetLost = False
isPIDTaskOpen = False
lock = Lock()


def millis():
    return int(round(time.time() * 1000))


class Pixhawk:
    def __init__(self):
        self.connection = mavutil.mavlink_connection('udp:127.0.0.1:14550')
        # self.connection = mavutil.mavlink_connection('COM17',baud=57600)
        self.connection.wait_heartbeat()

    def set_mode(self, mode_name):
        mode_id = self.connection.mode_mapping()[mode_name]
        self.connection.mav.set_mode_send(
            self.connection.target_system,
            mavutil.mavlink.MAV_MODE_FLAG_CUSTOM_MODE_ENABLED,
            mode_id
        )

    def send_movement_command(self, roll=1500, pitch=1500, throttle=1000, yaw=1447):
        self.connection.mav.rc_channels_override_send(
            self.connection.target_system,  # target_system
            self.connection.target_component,  # target_component
            roll,    # Channel 1 (Roll)
            pitch,   # Channel 2 (Pitch)
            throttle,  # Channel 3 (Throttle)
            yaw,     # Channel 4 (Yaw)
            0, 0, 0, 0   # Remaining channels (if needed)
        )


class PID:
    def __init__(self, Kp, Ki, Kd):
        self.Kp = Kp
        self.Ki = Ki
        self.Kd = Kd
        self.previous_error = 0
        self.integral = 0
        self.last_time = millis()

    def update(self, setpoint, measured_value):
        current_time = millis()
        dt = (current_time - self.last_time) / \
            1000.0  # Convert milliseconds to seconds

        error = setpoint - measured_value
        self.integral += error * dt
        derivative = (error - self.previous_error) / dt if dt > 0 else 0

        output = self.Kp * error + self.Ki * self.integral + self.Kd * derivative

        self.previous_error = error
        self.last_time = current_time

        return output

    def reset(self):
        self.integral = 0
        self.previous_error = 0
        self.last_time = millis()


# Initialize PID controllers
pidX = PID(Kp=0.2, Ki=0.005, Kd=0.03)
pidY = PID(Kp=0.2, Ki=0.005, Kd=0.03)


def start(pixy):
    global isTargetLost, isPIDTaskOpen, isPID

    while True:
        with lock:
            if (IHA["MODE"] == 2 and not isTargetLost) or IHA["MODE"] == 4:
                isPID = True
                isTargetLost = False
                if not isPIDTaskOpen:
                    isPIDTaskOpen = True
                    Thread(target=PIDTask,args=(pixy,)).start()
            else:
                isPID = False
                isTargetLost = False


def PIDTask(connection):
    global isPID, isPIDTaskOpen, isTargetLost

    with lock:
        if Target["x"] != -1:
            connection.set_mode('FBWA')
        currentXAngle = 1500
        currentYAngle = 1500

    setpointX = CAMERA["width"] / 2
    setpointY = CAMERA["height"] / 2

    print(setpointX, setpointY)

    pidX.reset()
    pidY.reset()
    pidTimeoutMillis = millis()
    print(isPID)

    while isPID:
        with lock:
            if ((millis() - pidTimeoutMillis) >= 500):
                pidX.reset()
                pidY.reset()
                isTargetLost = True
                break

            if Target["x"] != -1:
                pidTimeoutMillis = millis()
                currentXAngle -= pidX.update(setpointX, Target["x"])
                currentYAngle -= pidY.update(setpointY, Target["y"])

                if currentXAngle > 1900:
                    currentXAngle = 1900
                elif currentXAngle < 1100:
                    currentXAngle = 1100

                if currentYAngle > 1900:
                    currentYAngle = 1900
                elif currentYAngle < 1100:
                    currentYAngle = 1100

                print(
                    f"X: {currentXAngle}\t\tY: {currentYAngle}\t\t Target: {Target['x']} {Target['y']}")
                time.sleep(0.1)
                connection.send_movement_command(roll=int(currentXAngle), pitch=int(currentYAngle), throttle=1500)

    with lock:
        isPIDTaskOpen = False
