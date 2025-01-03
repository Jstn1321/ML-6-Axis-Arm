import serial
import time
import invKine
import numpy

arduino = serial.Serial(port='COM5', baudrate=115200, timeout=1)
time.sleep(2) 

message = "m"

arduino.write(message.encode()) 