
from data import *
from fastapi import FastAPI,Request
from threading import Thread
import usb 
import uvicorn
from pydantic import BaseModel
#Thread(target=usb.start).start()
print("Working")

app = FastAPI()

class IHAData(BaseModel):
    Lat : float = -1
    Long : float = -1


@app.get("/")
def Home():
    return "fuck off pls"


@app.get("/IHA")
def IHALat():
    return IHA

@app.post("/IHA/5")
async def IHALatss(request: IHAData):
    #print(await request.body())
    IHA.update({"Lat": request.Lat, "Long": request.Long})      
    return request

@app.get("/IKA")
def IHALat():
    return IKA

if __name__ == '__main__':
    uvicorn.run(app,port=80)
      
