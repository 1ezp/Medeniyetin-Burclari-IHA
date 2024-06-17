import socketserver
from threading import Thread
import json
import time
import usb 
from data import *


Thread(target=usb.start).start()

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
                else:
                    response = json.dumps({
                        "error": "Invalid request"
                    })
                
                # Send the response
                self.request.sendall(response.encode('utf-8'))

            except ConnectionResetError:
                print("Connection reset by peer")
                break
            except ConnectionAbortedError:
                print("Connection aborted by peer")
                break
            except Exception as e:
                print(f"An error occurred: {e}")
                break

class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

if __name__ == "__main__":
    HOST, PORT = '0.0.0.0', 12345

    server = ThreadedTCPServer((HOST, PORT), RequestHandler)
    print('Server started, waiting for connections...')
    with server:
        server.serve_forever()
