from data import *
import serial
from threading import Thread
import socketServer
import usbReciver
import IHAConnection 
import pixHawk

from trackSystem import main as trackSystem


Thread(target=usbReciver.main).start()
Thread(target=IHAConnection.start).start()
Thread(target=socketServer.start).start()
#Thread(target=pixHawk.start).start()

#Thread(target=trackSystem.main).start()