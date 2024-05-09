from data import *
import serial
import serial.tools.list_ports
import os,time

port = "COM5"
ser = serial.Serial(port, 115200, timeout=.1)

def start():

   while True:
      try:
         recivedData = ser.readline().decode()
         if recivedData != '':
            data = recivedData.split(",")
            if data[0] == 0 and data[1] == 0:
               IHA.update({"Lat": -1, "Long": -1})   
            else: 
               IHA.update({"Lat": float(data[0]), "Long": float(data[1])})                  
      except:
         pass

"""       
      #if recivedData != '':
      try:
         recivedData = ser.readline().decode()
         data = recivedData.split(",")
         if data[0] == '0.000000' and data[1] == '0.000000':
            IHA.update({"Lat": -1, "Long": -1})   
         else: 
            IHA.update({"Lat": float(data[0]), "Long": float(data[1])})   
            
         print(data)
      except:
         pass
       """
      


if __name__ == "__main__":
   start()