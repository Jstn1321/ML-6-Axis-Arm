import tensorflow as tf
import numpy as np
import os
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from tensorflow.keras.optimizers import RMSprop
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.utils import load_img, img_to_array
import pygame
import pygame.camera
import subprocess
import sys
from PIL import Image
import cv2

#train_green_dir = os.path.join('./bog/green')
train_green_dir = os.path.join('bog/green/')
#PycharmProjects/ImplementModel/
#train_blue_dir = os.path.join('./bog/blue')
train_blue_dir = os.path.join('bog/blue/')

train_green_names = os.listdir(train_green_dir)
#print(train_green_names[:10])

train_blue_names = os.listdir(train_blue_dir)
#print(train_blue_names[:10])

#print('green:', len(os.listdir(train_green_dir)))
#print('blue:', len(os.listdir(train_blue_dir)))

# Index for iterating over images
model = tf.keras.models.load_model('myModel.keras')
#print(images)
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
        pygame.image.save(image, "bog/liveTest/filename.jpg")

    # if camera is not detected the moving to else part
    else:
        print("No camera on current device")

    images = os.listdir("bog/liveTest/")
    blue = False

    for i in images:
        path = 'bog/liveTest/' + i
        img = load_img(path, target_size=(300, 300))
        x = img_to_array(img)
        x /= 255

        x = np.expand_dims(x, axis=0)

        images = np.vstack([x])
        classes = model.predict(images, batch_size=1)
        print(classes[0])
        if classes[0]>0.5:
            print(i + " is a green box")
            blue = False
        else:
            print(i + " is a blue box")
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
        print(where_list)

    if (blue == True):
        for k in range(len(imga)):
                imgaB.append(imga[k][2])
        #print(imgaB)
        where_list = imgaB.index(max(imgaB))
        where_list = where_list + 1
        print(where_list)

    row = (where_list/352)//1
    temp = where_list - row
    column = where_list - ((row*352)+1)
    row = row + 20
    print(row)
    print(column)

    plt.title("Box Image")
    plt.xlabel("X pixel scaling")
    plt.ylabel("Y pixels scaling")
    plt.plot(column, row, marker='v', color="purple")

    image = mpimg.imread("bog/liveTest/filename.jpg")
    plt.imshow(image)
    plt.show()

    again = input("Try again?(1/0 (y/n)")
    if again == "0":
        loop = False
    else:
        loop = True