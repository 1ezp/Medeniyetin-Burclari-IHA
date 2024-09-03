import time,math
from data import *
from pymavlink import mavutil



class Pixhawk:
    def __init__(self, conn, **kwargs):
        # self.connection = mavutil.mavlink_connection('udp:127.0.0.1:14550')
        # self.connection = mavutil.mavlink_connection('COM17',baud=57600)
        self.connection = mavutil.mavlink_connection(conn)
        self.connection.wait_heartbeat()
        print(f"Heartbeat from system (system {self.connection.target_system} component {self.connection.target_component})")
        rate = 50
        self.connection.mav.request_data_stream_send(self.connection.target_system, self.connection.target_component, mavutil.mavlink.MAV_DATA_STREAM_ALL, rate, 1)
        

    def set_mode(self, mode_name):
        mode_id = self.connection.mode_mapping()[mode_name]
        self.connection.mav.set_mode_send(
            self.connection.target_system,
            mavutil.mavlink.MAV_MODE_FLAG_CUSTOM_MODE_ENABLED,
            mode_id
        )
        return True
    
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
    
    def sendArmCommand(self,arm:int, force = False):
        """
            Arm: 1
            Disarm: 0
        """
        self.connection.mav.command_long_send(
            self.connection.target_system,
            self.connection.target_component,
            mavutil.mavlink.MAV_CMD_COMPONENT_ARM_DISARM,
            0,
            arm,
            2989 if force else 0,
            0,0,0,0,0
        )
    
    def fetchData(self):
        while True:
            msg = self.connection.recv_match(blocking=True)
            if not msg:
                print(msg)
                continue
            
            if msg.get_type() == 'ATTITUDE':
                roll = math.degrees(msg.roll)
                pitch = math.degrees(msg.pitch)
                IHA.update({ "roll": float(roll), "pitch": float(pitch)})
                
            elif msg.get_type() == 'GPS_RAW_INT':
                lat = msg.lat / 1e7 
                lon = msg.lon / 1e7 
                IHA.update({"Lat": float(lat), "Long": float(lon)})
                
            elif msg.get_type() == 'VFR_HUD':
                speed = msg.groundspeed
                IHA.update({ "groundSpeed": float(speed)})
                
            elif msg.get_type() == "GLOBAL_POSITION_INT":
                relative_alt = msg.relative_alt / 1000.0
                IHA.update({ "relative_alt": float(relative_alt)})
            elif msg.get_type() == "BATTERY_STATUS":
                voltage = msg.voltages[0] / 1000
                IHA.update({ "batteryVoltage": float(voltage)})


def start():
    port = 'COM17' 
    pix = mavutil.mavlink_connection(port, baud=57600)
    pix.wait_heartbeat()
    print(f"Heartbeat from system (system {pix.target_system} component {pix.target_component})")
    rate = 50
    pix.mav.request_data_stream_send(pix.target_system, pix.target_component, mavutil.mavlink.MAV_DATA_STREAM_ALL, rate, 1)
    
    while True:
        msg = pix.recv_match(blocking=True)
        if not msg:
            print(msg)
            continue
        
        if msg.get_type() == 'ATTITUDE':
            roll = math.degrees(msg.roll)
            pitch = math.degrees(msg.pitch)
            IHA.update({ "roll": float(roll), "pitch": float(pitch)})
            
        elif msg.get_type() == 'GPS_RAW_INT':
            lat = msg.lat / 1e7 
            lon = msg.lon / 1e7 
            IHA.update({"Lat": float(lat), "Long": float(lon)})
            
        elif msg.get_type() == 'VFR_HUD':
            speed = msg.groundspeed
            IHA.update({ "groundSpeed": float(speed)})
        elif msg.get_type() == "GLOBAL_POSITION_INT":
            relative_alt = msg.relative_alt / 1000.0
            IHA.update({ "relative_alt": float(relative_alt)})

if __name__ == "__main__":  
    start()
