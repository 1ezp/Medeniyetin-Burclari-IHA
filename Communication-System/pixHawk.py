import time,math
from data import *
from pymavlink import mavutil




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
