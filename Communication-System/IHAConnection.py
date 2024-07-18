from data import *
import socketserver
from threading import Thread




class RequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        print(f'Connected IHA by {self.client_address}')
        while True:
            try:
                data = self.request.recv(1024).decode('utf-8').split(":")
                response = f"{IHA['MODE']}:{Controller['x']}:{Controller['y']}:{IHA['motorSpeed']}:{Target['x']}:{Target['y']}"
                self.request.sendall(response.encode('utf-8'))
                #IHA.update({"Lat": float(data[0]), "Long": float(data[1])})
            except Exception as e:
                print(f"An error occurred: {e}")
                break

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

def start():
    HOST = '0.0.0.0'
    PORT = 50
    server = ThreadedTCPServer((HOST, PORT), RequestHandler)
    with server:
        server.serve_forever()
if __name__ == "__main__":
    start()
