from threading import Thread
from data import *

from pixHawk import Pixhawk
import socketServer
import usbReciver

import IHAConnection
import IKAConnection

import PID
from trackSystem import main as trackSystem

pixy = Pixhawk('udp:127.0.0.1:14550')

Thread(target=pixy.fetchData).start()
Thread(target=socketServer.start, args=(pixy,)).start()
# Thread(target=usbReciver.main).start()

# Thread(target=IHAConnection.start).start()
# Thread(target=IKAConnection.start).start()

# Thread(target=trackSystem.main).start()
Thread(target=PID.start, args=(pixy,)).start()