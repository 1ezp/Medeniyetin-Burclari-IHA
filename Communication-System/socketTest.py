import socket
mytcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
mytcp.bind(('0.0.0.0', 55))
mytcp.listen(1)
connection, addr = mytcp.accept();
print('Connected with ' + addr[0] + ':' + str(addr[1]))
connection.send(b'Connection: OK\n')
while True:
 data = connection.recv(1024)
 if not data: break
 print(data.decode())
connection.close()