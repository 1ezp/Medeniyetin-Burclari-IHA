## This folder contains the necessary files to stream the camera input from RaspberryPi 3B+ to a webserver

<p>Download and install <a href="https://www.raspberrypi.com/software/">imager</a> program and setup the sd card for the raspberry</p>
<p>Connect to the RaspberryPi with either a monitor or using ssh</p>
<p>Using raspi-config make sure to open VNC for future troubleshooting</p>

<p>You can disable built-in wifi by editing <strong>/etc/network/interfaces</strong> by adding</p>

```
auto wlan0
iface wlan0 inet manual
```

<p>In order to execute a command at the start of the Raspberry Pi you can make a cron job using <code>sudo crontab -e</code></p>

```
@reboot sudo python3 /home/iha/Desktop/server.py &
```

<p>The project uses <code>picamera2</code> lib in python</p>
<p>The directory for the stream is <strong>/stream.mjpg</strong></p>
