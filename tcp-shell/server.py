import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("127.0.0.1", 8080))

s.listen(1)
                                                        
print ('[+] Listening for incoming TCP connection on port 8080')
conn, addr = s.accept()
print ('[+]', addr, ' connected')

while True:
    command = input("sh> ")
    conn.send(command.encode())
    print(conn.recv(1024).decode())