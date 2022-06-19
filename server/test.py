#Test server in python. Just for trying stuff

import socket
host = ''
port = 4448
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen()

while True:
    client, address = server.accept()
    print("+1 user")
    client.send("successfully connected | welcome test user.".encode('utf-8'))
