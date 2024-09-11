from data import *
import serial
import serial.tools.list_ports
import os,time
from threading import Lock

lock = Lock()

def connect_serial(port):
    while True:
        try:
            ser = serial.Serial(port, 9600, timeout=.1)
            return ser
        except serial.SerialException:
            pass
  
    
def main():
    port = "COM11"
    ser = connect_serial(port)
    while True:
        try:
            recivedData = ser.readline().decode()
            if recivedData != '':
                data = recivedData.split(":")
                with lock:
                    IHA.update({"MODE": int(data[0])})
            time.sleep(0.01)  # Add a small sleep to give some breathing room
        except serial.SerialException:
            with lock:
                IHA.update({"MODE": 1})
            if ser and ser.isOpen():
                ser.close()
            ser = connect_serial(port)
        except Exception as e:
            with lock:
                IHA.update({"MODE": 1})
            print(e)


if __name__ == "__main__":
   main()
   