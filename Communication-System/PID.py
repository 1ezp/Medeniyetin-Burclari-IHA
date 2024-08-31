from pymavlink import mavutil
import time


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
        throttle, # Channel 3 (Throttle)
        yaw,     # Channel 4 (Yaw)
        0, 0, 0, 0   # Remaining channels (if needed)
        
    )


connection = mavutil.mavlink_connection('udp:127.0.0.1:14550')
connection.wait_heartbeat()

set_mode(connection, 'FBWA')

try:
    while True:
        send_movement_command(connection, roll=1900, pitch=1900, throttle=1900)  # Increase roll to move right
        time.sleep(0.3)
        break
finally:
    set_mode(connection, 'AUTO')
    send_movement_command(connection, roll=1100, pitch=1100, throttle=1300)
    