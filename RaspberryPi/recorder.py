from gpiozero import Button, LED
from picamera2 import Picamera2
from signal import pause
from datetime import datetime
import os
from picamera2.encoders import H264Encoder
from threading import Timer

# Initialize the camera and button
camera = Picamera2()
camera.configure(camera.create_video_configuration(
    main={"size": (1920, 1080)}))  # Configure for high quality
button = Button(17)  # GPIO17 for the button press

# Initialize GPIO pin 27 for the external LED
led = LED(27)  # GPIO27 for the external LED

# State variables
recording = False
debounce_timer = None
debouncing = False  # To track if debounce is active

# Directory to save recordings
recording_directory = "/home/iha/Desktop/Recordings"

# Ensure the directory exists
os.makedirs(recording_directory, exist_ok=True)


def toggle_recording():
    global recording, debouncing, debounce_timer

    if debouncing:  # Ignore button press if debounce is active
        return

    # Activate debounce
    debouncing = True
    debounce_timer = Timer(1, reset_debounce)  # 1s debounce
    debounce_timer.start()

    if recording:
        print("Stopping recording...")
        camera.stop_recording()
        led.off()  # Turn off the external LED
        recording = False
    else:
        # Generate filename with date and time
        now = datetime.now()
        filename = now.strftime("%Y-%m-%d_%H-%M-%S.h264")
        filepath = os.path.join(recording_directory, filename)

        print(f"Starting recording: {filepath}")

        # Start recording to the file
        camera.start_recording(output=filepath, encoder=H264Encoder())
        led.on()  # Turn on the external LED
        recording = True


def reset_debounce():
    global debouncing
    debouncing = False  # Reset debounce state


# Bind button press to toggle_recording function
button.when_pressed = toggle_recording

# Keep the script running in a loop for continuous recording
print("Script running. Press the button to toggle recording.")
pause()
