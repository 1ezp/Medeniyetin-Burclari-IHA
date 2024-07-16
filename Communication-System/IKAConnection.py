from data import *
import socketserver
from threading import Thread




class RequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        print(f'Connected by {self.client_address}')
        while True:
            try:
                data = self.request.recv(1024).decode('utf-8').split(":")
                response = f"{IKA['Movment']}:{IHA['Turret']}"
                self.request.sendall(response.encode('utf-8')) 
                IKA.update({"Lat": float(data[0]), "Long": float(data[1])})
            except Exception as e:
                print(f"An error occurred: {e}")
                break

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

def start():
    HOST = '0.0.0.0'
    PORT = 100
    server = ThreadedTCPServer((HOST, PORT), RequestHandler)
    with server:
        server.serve_forever()