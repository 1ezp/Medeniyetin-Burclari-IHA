from data import *
import serial
import serial.tools.list_ports
import os,time


def start():
   # ihaLat:ihaLong:x:y:mode
   port = "COM8"
   ser = serial.Serial(port, 115200, timeout=.1)

   while True:
      try:
         recivedData = ser.readline().decode()
         if recivedData != '':
            data = recivedData.split(":")
            #print(f"Mode:{data[4]}\r")
            if data[0] == 0 and data[1] == 0:
               IHA.update({"Lat": -1, "Long": -1})   
            else: 
               IHA.update({"Lat": float(data[0]), "Long": float(data[1])})
               Target.update({"x":data[2],"y":data[3]})
               print("x:",data[2],"y:",data[3])
      except:
         pass

def connect_serial(port):
    while True:
        try:
            ser = serial.Serial(port, 9600, timeout=.1)
            return ser
        except serial.SerialException:
            pass
  
    
def main():
   # MODE:controllerX:controllerY:motorSpeed
   
   port = "COM11"
   ser = connect_serial(port)
   while True:
      try:
         recivedData = ser.readline().decode()
         print(recivedData)
         if recivedData != '':
            data = recivedData.split(":")
            MODE.update({"value": data[0]})
            Controller.update({"x": data[1], "y": data[2]})
            IHA.update({"motorSpeed": int(data[3])})
      except serial.SerialException:
         MODE.update({"value": 1})
         if ser and ser.isOpen():
            ser.close()
         ser = connect_serial(port)
      except Exception as e:
         MODE.update({"value": 1})
         print(e)

if __name__ == "__main__":
   main()