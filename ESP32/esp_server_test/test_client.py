import requests

dest_address = 'http://192.168.0.89:90/post'

while (True):

    data = input("Enter direction to move on map:")

    response = requests.post(dest_address, data={'data': data})

    print("Response from server:", response.text)


# #From Software Systems
# import socket

# server_name = 'localhost'
# server_port = 12000

# client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# client_socket.connect((server_name, server_port))

# print("TCP client running...")
# print("Connecting to server at IP: ", server_name, " PORT: ", server_port)

# msg = input("Enter a string to test if it is alphanumeric: ");

# client_socket.send(msg.encode())

# msg = client_socket.recv(1024)
# print(msg.decode())
# client_socket.close()