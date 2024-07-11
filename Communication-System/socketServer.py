import socketserver
import json

from data import *

class RequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        print(f'Connected by {self.client_address}')
        while True:
            try:
                # Read the client's request
                request = self.request.recv(1024).decode('utf-8').strip()
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
                else:
                    response = json.dumps({
                        "error": "Invalid request"
                    })
                
                self.request.sendall(response.encode('utf-8'))

            except Exception as e:
                print(f"An error occurred: {e}")
                break

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

def start():
    HOST, PORT = '127.0.0.1', 12345

    server = ThreadedTCPServer((HOST, PORT), RequestHandler)
    print('Server started, waiting for connections...')

    with server:
        server.serve_forever()
