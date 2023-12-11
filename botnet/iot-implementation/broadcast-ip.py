import serial

message = "close connections"

# Send message over com3
try:
    ser_com3 = serial.Serial('com3')
    ser_com3.write(message.encode())
    ser_com3.close()
    print("Message sent over com3")
except serial.SerialException:
    print("Failed to send message over com3")

# Send message over com5
try:
    ser_com5 = serial.Serial('com5')
    ser_com5.write(message.encode())
    ser_com5.close()
    print("Message sent over com5")
except serial.SerialException:
    print("Failed to send message over com5")
