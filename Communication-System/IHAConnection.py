from data import *
import socketserver
from threading import Thread

HOST = '0.0.0.0'
PORT = 12345


class RequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        print(f'Connected by {self.client_address}')
        while True:
            try:
                data = self.request.recv(1024).decode('utf-8')
                print(f"Received data: {data}")
                response = f"{MODE['value']}:{Controller['x']}:{Controller['y']}:{motorSpeed['value']}:{Target['x']}:{Target['y']}"
                self.request.sendall(response.encode('utf-8'))
            except:
                break

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

server = ThreadedTCPServer((HOST, PORT), RequestHandler)
with server:
    server.serve_forever()