#import tflite_runtime.interpreter as tflite
import numpy as np
import os
import tensorflow as tf
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
#from tensorflow.keras.optimizers import RMSprop
#from tensorflow.keras.preprocessing.image import ImageDataGenerator
#from tensorflow.keras.utils import load_img, img_to_array
import pygame
import pygame.camera
import subprocess
import sys
from PIL import Image
import cv2
import pathlib


model = tf.keras.models.load_model('myModel.keras')
tf.saved_model.save(model, "bog/")

"""
# Load the TFLite model and allocate tensors.
interpreter = tflite.Interpreter(model_path="model.tflite")
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
print(output_data)

# input details
print(input_details)
# output details
print(output_details)
pygame.camera.init()
camlist = pygame.camera.list_cameras()
loop = True
while(loop):
  if camlist:

      # initializing the cam variable with default camera
      cam = pygame.camera.Camera(camlist[0], (300, 300))

      # opening the camera
      cam.start()
      #input("Press Enter to take the picture")
      # capturing the single image
      image = cam.get_image()

        # saving the image
      pygame.image.save(image, "PycharmProjects/ImplementModel/bog/liveTest/filename.jpg")

    # if camera is not detected the moving to else part
  else:
      print("No camera on current device")

  images = os.listdir("PycharmProjects/ImplementModel/bog/liveTest/")
  blue = False

  for file in pathlib.Path('bog/liveTest/').iterdir():
    # read and resize the image
    img = cv2.imread(r"{}".format(file.resolve()))
    new_img = cv2.resize(img, (300, 300))
    new_img = np.float32(new_img)

    # input_details[0]['index'] = the index which accepts the input
    interpreter.set_tensor(input_details[0]['index'], [new_img])

    # run the inference
    interpreter.invoke()

    # output_details[0]['index'] = the index which provides the input
    output_data = interpreter.get_tensor(output_details[0]['index'])

    #print("For file {}, the output is {}".format(file.stem, output_data))
    if output_data > 0.5:
      print("green box")
      blue = False
    else:
      print("blue box")
      blue = True

    im = Image.open('PycharmProjects/ImplementModel/bog/liveTest/filename.jpg', 'r')
    pix_val = list(im.getdata())
    imga = [list(ele) for ele in pix_val]
    #imga = np.array(cv2.imread('PycharmProjects/ImplementModel/bog/liveTest/filename.jpg'))
    imgaG = []
    imgaB = []
    where_list = 0
    if (blue == False):
        for k in range(len(imga)):
            imgaG.append(imga[k][1])
        print(imgaG)
        where_list = imgaG.index(max(imgaG))
        where_list = where_list + 1
        print(where_list)

    if (blue == True):
        for k in range(len(imga)):
                imgaB.append(imga[k][2])
        print(imgaB)
        where_list = imgaB.index(max(imgaB))
        where_list = where_list + 1
        print(where_list)

    row = (where_list/320)//1
    temp = where_list - row
    column = where_list - ((row*320)+1)
    row = row + 20
    print(row)
    print(column)

    plt.title("Box Image")
    plt.xlabel("X pixel scaling")
    plt.ylabel("Y pixels scaling")
    plt.plot(column, row, marker='v', color="purple")

    image = mpimg.imread("PycharmProjects/ImplementModel/bog/liveTest/filename.jpg")
    plt.imshow(image)
    plt.show()

    again = input("Try again?(1/0 (y/n)")
    if again == "0":
        loop = False
    else:
        loop = True
"""