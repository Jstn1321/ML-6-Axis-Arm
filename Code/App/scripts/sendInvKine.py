import serial
import time
import invKine
import numpy
import struct

arduino = serial.Serial(port='COM5', baudrate=115200, timeout=1)
time.sleep(2)  
"""
# Generate joint angles
jointAngles = invKine.ik([0.52, 0.1, 0.3])

# Prepare data for sending
data_string = ','.join(map(str, jointAngles)) + '\n'  # Add newline for Arduino to read

print(invKine.ik([0.52, 0.1, 0.3]))
# Wait for a response
while True:
    arduino.write(data_string.encode())  # Send to Arduino
    response = arduino.readline().decode().strip()
    if response:
        jointAngles = list(map(float, response.split(',')))
        print(jointAngles)
"""
def sendInvKineToArd (list = [], isblue = 0):
    degrees = invKine.ik(list)
    degrees.append(isblue)
    data_string = struct.pack('<9l', *degrees)
    arduino.write(b'#')
    arduino.write(data_string) 
    """
    #for i in range(50):
    data_string = ','.join(map(str, invKine.ik(list))) + '\n'
    arduino.write(data_string.encode()) 
    
    while True:
        response = arduino.readline().decode().strip()
        print(response)
    """
    """
    while  True:
        data_string = ','.join(map(str, invKine.ik(list))) + '\n'
        arduino.write(data_string.encode())
        response = arduino.readline().decode().strip()
        print(response)
    """
    