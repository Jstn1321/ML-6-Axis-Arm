#!/usr/bin/env python
import sys
import PySimpleGUI as sg
import tflite_runtime.interpreter as tflite
import numpy as np
import os
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
#from tensorflow.keras.optimizers import RMSprop
#from tensorflow.keras.preprocessing.image import ImageDataGenerator
#from tensorflow.keras.utils import load_img, img_to_array
import subprocess
import sys
from PIL import Image, ImageDraw
import cv2
import pathlib
import pygame
import pygame.camera
from tensorflow.keras.optimizers import RMSprop
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.utils import load_img, img_to_array
import time
import psutil

"""
    Copyright 2023 PySimpleSoft, Inc. and/or its licensors. All rights reserved.

    Redistribution, modification, or any other use of PySimpleGUI or any portion thereof is subject to the terms of the PySimpleGUI License Agreement available at https://eula.pysimplegui.com.

    You may not redistribute, modify or otherwise use PySimpleGUI or its contents except pursuant to the PySimpleGUI License Agreement.
"""


# Load the TFLite model and allocate tensors.
interpreter = tflite.Interpreter(model_path="newkerasmodel.tflite")
interpreter.allocate_tensors()

# Get input and output tensors.
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Test the model on random input data.
input_shape = input_details[0]['shape']
input_data = np.array(np.random.random_sample(input_shape))
input_data = np.float32(input_data)
interpreter.set_tensor(input_details[0]['index'], input_data)

interpreter.invoke()

# The function `get_tensor()` returns a copy of the tensor data.
# Use `tensor()` in order to get a pointer to the tensor.
output_data = interpreter.get_tensor(output_details[0]['index'])


# input details
# output details

#os.environ['PYGAME_CAMERA'] = 'opencv'

cam = cv2.VideoCapture(0)
cam.set(3, 300)
cam.set(4, 300)
cam.set(6, cv2.VideoWriter.fourcc('M', 'J', 'P', 'G'))

layout = [
          [sg.Button('Preview', button_color=('white', 'black'), key='prev'),
           sg.Button('Take a Picture', button_color=('white', 'black'), key='pic'),
           sg.Button('Close all Windows', button_color=('white', 'firebrick3'), key='close')]
          ]

window = sg.Window("Robot Arm Control Panel", layout, auto_size_buttons=False, default_button_element_size=(12,1), use_default_focus=False, finalize=True)

recording = have_data = False
while True:
    event, values = window.read()
    if event == sg.WINDOW_CLOSED:
        break
    if event == 'close':
        cv2.destroyAllWindows()
        for proc in psutil.process_iter():
            if proc.name() == "display":
                proc.kill()
    if event == 'prev':
        while True:
            ret, frame = cam.read()
            cv2.imshow('Imagetest', frame)
            k = cv2.waitKey(1)
            if k != -1:
                break
                cv2.destroyAllWindows()
    if event == 'pic':
        cv2.destroyAllWindows()
        k = 1
        ret, frame = cam.read()
        cv2.imwrite("/home/amogusbobby/Python/ConvertTFtoTFLite/bog/liveTest/filename.jpg", frame)
        cam.release
        print("Took Picture")
        blue = False
        #pygame.image.save(image, "bog/liveTest/filename.jpg")
        for file in pathlib.Path('bog/liveTest/').iterdir():
        #for i in images:
            # read and resize the image
            """
            img = cv2.imread(r"{}".format(file.resolve()))
            img = cv2.resize(img, (300, 300))
            x = img_to_array(img)
            x /= 255
            new_img = np.float32(x)
            #new_img = np.expand_dims(new_img, axis = 0)
            #new_img = np.vstack([new_img])
            """
            path = 'bog/liveTest/filename.jpg'
            img = load_img(path, target_size=(300, 300))
            x = img_to_array(img)
            x /= 255
            new_img = np.float32(x)
            
            
            # input_details[0]['index'] = the index which accepts the input
            interpreter.set_tensor(input_details[0]['index'], [new_img])

            # run the inference
            interpreter.invoke()

            # output_details[0]['index'] = the index which provides the input
            output_data = interpreter.get_tensor(output_details[0]['index'])

            #print("For file {}, the output is {}".format(file.stem, output_data))
            print(output_data)
            if output_data > 0.5:
              print("green box")
              blue = False
            else:
              print("blue box")
              blue = True

        im = Image.open('bog/liveTest/filename.jpg', 'r')
        pix_val = list(im.getdata())
        imga = [list(ele) for ele in pix_val]
        #imga = np.array(cv2.imread('PycharmProjects/ImplementModel/bog/liveTest/filename.jpg'))
        imgaG = []
        imgaB = []
        where_list = 0
        if (blue == False):
            for k in range(len(imga)):
                imgaG.append(imga[k][1])
            #print(imgaG)
            where_list = imgaG.index(max(imgaG))
            where_list = where_list + 1
            #print(where_list)

        if (blue == True):
            for k in range(len(imga)):
                    imgaB.append(imga[k][2])
            
            where_list = imgaB.index(max(imgaB))
            where_list = where_list + 1
                

        row = (where_list/352)//1
        temp = where_list - row
        column = where_list - ((row*352)+1)
        row = row + 20
        print(row)
        print(column)

        image = Image.open("bog/liveTest/filename.jpg")
        draw = ImageDraw.Draw(image)
        draw.ellipse((column, row, column + 10, row+10), fill = (255, 100, 100,255))
        #outline = "purple", width = 25)
        image.show()
        
