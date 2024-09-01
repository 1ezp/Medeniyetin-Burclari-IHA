from pymavlink import mavutil
import time
from data import IHA, CAMERA, Target
from threading import Thread


def set_mode(connection, mode_name):
    """
    Set the mode of the Pixhawk.
    """
    mode_id = connection.mode_mapping()[mode_name]
    connection.mav.set_mode_send(
        connection.target_system,
        mavutil.mavlink.MAV_MODE_FLAG_CUSTOM_MODE_ENABLED,
        mode_id
    )


def send_movement_command(connection, roll=1500, pitch=1500, throttle=1000, yaw=1447):
    """
    Send movement commands to the Pixhawk using RC channel override.

    :param connection: MAVLink connection object
    :param roll: Value for roll (Channel 1), default is 1500 (neutral)
    :param pitch: Value for pitch (Channel 2), default is 1500 (neutral)
    :param throttle: Value for throttle (Channel 3), default is 1000 (neutral)
    :param yaw: Value for yaw (Channel 4), default is 1500 (neutral)
    """
    connection.mav.rc_channels_override_send(
        connection.target_system,  # target_system
        connection.target_component,  # target_component
        roll,    # Channel 1 (Roll)
        pitch,   # Channel 2 (Pitch)
        throttle,  # Channel 3 (Throttle)
        yaw,     # Channel 4 (Yaw)
        0, 0, 0, 0   # Remaining channels (if needed)

    )


connection = mavutil.mavlink_connection('udp:127.0.0.1:14550')
connection.wait_heartbeat()


isPID = False
targetLostOverride = False
isPIDTaskOpen = True


def modeAdjuster():

    global isPID, targetLostOverride, isPIDTaskOpen

    while True:
        # if (IHA["MODE"] == 2 and not targetLostOverride) or IHA["MODE"] == 4:
        if True:
            set_mode(connection, 'FBWA')
            isPID = True
            targetLostOverride = False
            if isPIDTaskOpen:
                Thread(target=PIDTask).start()
        else:
            isPID = False
            targetLostOverride = False
            set_mode(connection, 'AUTO')


def millis():
    return int(round(time.time() * 1000))


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
        # Optionally reset last_time to avoid large dt when restarting
        self.last_time = millis()


pidX = PID(Kp=1.0, Ki=0.1, Kd=0.01)
pidY = PID(Kp=1.0, Ki=0.1, Kd=0.01)


def PIDTask():

    global isPID, isPIDTaskOpen, targetLostOverride

    isPIDTaskOpen = False

    currentXAngle = 1500
    currentYAngle = 1500

    setpointX = CAMERA["width"]
    setpointY = CAMERA["height"]

    pidX.reset()
    pidY.reset()
    pidTimeoutMillis = millis()

    while isPID:

        if ((millis() - pidTimeoutMillis) >= 1000):

            pidX.reset()
            pidY.reset()

            targetLostOverride = True
            break

        if Target["x"] != -1:

            pidTimeoutMillis = millis()

            if not pidX.active:
                pidX.start()
            currentXAngle += pidX.update(setpointX, Target["x"])
            currentYAngle += pidY.update(setpointY, Target["y"])

            print(f"X: {currentXAngle}\t\tY: {currentYAngle}")
            send_movement_command(
                connection, roll=currentXAngle, pitch=currentYAngle, throttle=1500)

    isPIDTaskOpen = True
