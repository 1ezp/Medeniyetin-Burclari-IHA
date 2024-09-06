## This folder contains the necessary files to stream the camera input from RaspberryPi 3B+ to a webserver

<p>Download and install [imager](https://www.raspberrypi.com/software/) program and setup the sd card for the raspberry</p>
<p>Connect to the RaspberryPi with either a monitor or using ssh</p>
<p>Using raspi-config make sure to open VNC for future troubleshooting</p>

<p>You can disable built-in wifi by editing <strong>/etc/network/interfaces</strong> by adding</p>

```
auto wlan0
iface wlan0 inet manual
```

<p>In order to execute a command at the start of the Raspberry Pi you can make a cron job using `sudo crontab -e`</p>

```
@reboot sudo python3 /home/iha/Desktop/mjpeg_server_2.py &
```

<p>The project uses `picamera2` lib in python</p>
<p>The directory for the stream is <strong>/stream.mjpg</strong></p>
