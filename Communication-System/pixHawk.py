import time
from data import *
from pymavlink import mavutil




def start():
    port = 'COM14' 
    pix = mavutil.mavlink_connection(port, baud=115200)
    pix.wait_heartbeat()
    print(f"Heartbeat from system (system {pix.target_system} component {pix.target_component})")
    rate = 50
    pix.mav.request_data_stream_send(pix.target_system, pix.target_component, mavutil.mavlink.MAV_DATA_STREAM_ALL, rate, 1)
    
    while True:
        msg = pix.recv_match(type='VFR_HUD', blocking=True)
        if msg:
            speed = msg.groundspeed
            IHA.update({ "groundSpeed": float(speed)})
            print(f"Ground speed: {speed} m/s")


if __name__ == "__main__":
    start()
