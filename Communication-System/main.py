from threading import Thread
from data import *

from pixHawk import Pixhawk
import socketServer
import usbReciver

import IHAConnection
import IKAConnection

import PID
from trackSystem.main import VideoTracker

# pixy = Pixhawk('udp:127.0.0.1:14550')
pixy = Pixhawk('tcp:127.0.0.1:5760')

tracker = VideoTracker("http://192.168.10.123:7123/stream.mjpg")
# Thread(target=pixy.fetchData).start()
# Thread(target=socketServer.start, args=(pixy,)).start()
# Thread(target=usbReciver.main).start()

# Thread(target=IHAConnection.start).start()
# Thread(target=IKAConnection.start).start()

Thread(target=tracker.start).start()
# Thread(target=PID.start, args=(pixy,)).start()