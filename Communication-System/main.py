from data import *

import serial
from threading import Thread
import usb 

from ..trackSystem import main as trackSystem


Thread(target=usb.main).start()
Thread(target=serial.main).start()

while True:
    print("mode:",MODE["value"])