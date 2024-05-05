
from data import *
from fastapi import FastAPI
from threading import Thread
import usb 
import uvicorn

Thread(target=usb.start).start()
print("Working")

app = FastAPI()

@app.get("/")
def Home():
    return "fuck off pls"


@app.get("/IHA")
def IHALat():
    return IHA

if __name__ == '__main__':
    uvicorn.run(app,port=80)
      
