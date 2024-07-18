from data import *
import serial
import serial.tools.list_ports
import os,time



def connect_serial(port):
    while True:
        try:
            ser = serial.Serial(port, 9600, timeout=.1)
            return ser
        except serial.SerialException:
            pass
  
    
def main():
   # MODE:controllerX:controllerY:motorSpeed:Movment:Turret
   
   port = "COM11"
   ser = connect_serial(port)
   while True:
      try:
         recivedData = ser.readline().decode()
         #print(recivedData)
         if recivedData != '':
            data = recivedData.split(":")
            Controller.update({"x": data[1], "y": data[2]})
            IHA.update({"motorSpeed": int(data[3]),"MODE":int(data[0])})
            IKA.update({"Movment":int(data[4]),"Turret":int(data[5])})

            
      except serial.SerialException:
         IHA.update({"MODE": 1})
         if ser and ser.isOpen():
            ser.close()
         ser = connect_serial(port)

      except Exception as e:
         IHA.update({"MODE": 1})
         print(e)

if __name__ == "__main__":
   main()
   