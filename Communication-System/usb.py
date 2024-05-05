from data import *
import serial
import serial.tools.list_ports
import os

port = "COM5"
ser = serial.Serial(port, 115200, timeout=.1)
ser.close()
ser.open()
def start():
   
   while True:
      ser.reset_input_buffer() 
      #line = ser.readline().decode("utf-8")
      line =  ser.read_until('\n').decode()
      if line != '':
         try:
            data = line.split(",")
            IHA.update({"IHALat": float(data[0]), "IHALong": float(data[1])})   
            """ print(data)
            ser.flush() """
         except:
            pass


if __name__ == "__main__":
   start()