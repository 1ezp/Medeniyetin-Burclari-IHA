import socketserver
import json
from data import *

class RequestHandler(socketserver.BaseRequestHandler):
    def __init__(self, *args, pixy=None, **kwargs):
        self.pixy = pixy
        super().__init__(*args, **kwargs)

    def handle(self):
        print(f'Connected by {self.client_address}')
        while True:
            try:
                # Read the client's request
                request = self.request.recv(1024).decode('utf-8').strip()
                print(f"Request: {request}")
                if not request:
                    break
                
                if request == 'IHA':
                    response = json.dumps(IHA)
                elif request == 'IKA':
                    response = json.dumps(IKA)
                elif request == 'YER':
                    response = json.dumps(YER)
                elif request == 'Target':
                    response = json.dumps(Target)
                elif 'Camera' in request:
                    _,width, height = request.split(':')
                    CAMERA.update({
                        "width": float(width),
                        "height": float(height)
                    })
                    response = "ok"
                elif 'arm' in request:
                    _, arm, force = request.split(':')
                    self.pixy.sendArmCommand(int(arm), int(force))  # Use pixy instance here
                    response = "ok"
                else:
                    response = json.dumps({
                        "error": "Invalid request"
                    })
                
                self.request.sendall(response.encode('utf-8'))
                print(CAMERA)
            except Exception as e:
                print(f"An error occurred: {e}")
                break

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    def __init__(self, server_address, RequestHandlerClass, pixy=None):
        self.pixy = pixy
        super().__init__(server_address, RequestHandlerClass)

    def finish_request(self, request, client_address):
        self.RequestHandlerClass(request, client_address, self, pixy=self.pixy)

def start(pixy):
    HOST, PORT = '127.0.0.1', 12345

    server = ThreadedTCPServer((HOST, PORT), RequestHandler, pixy=pixy)
    print('Server started, waiting for connections...')

    with server:
        server.serve_forever()
