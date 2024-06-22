from data import *
import serial
import serial.tools.list_ports
import os,time

"ihaLat:ihaLong:x:y:mode"

def start():
   port = "COM8"
   ser = serial.Serial(port, 115200, timeout=.1)

   while True:
      try:
         recivedData = ser.readline().decode()
         if recivedData != '':
            data = recivedData.split(":")
            if data[0] == 0 and data[1] == 0:
               IHA.update({"Lat": -1, "Long": -1})   
            else: 
               IHA.update({"Lat": float(data[0]), "Long": float(data[1])})
               Target.update({"x":data[2],"y":data[3]})
               print("x:",data[2],"y:",data[3])
      except:
         pass

      


if __name__ == "__main__":
   start()