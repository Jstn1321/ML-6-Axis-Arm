import tensorflow as tf
import numpy as np
import os
from tensorflow.keras.optimizers import RMSprop
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.utils import load_img, img_to_array
import subprocess
import sys
from PIL import Image
import cv2

model = tf.keras.models.load_model('assets/MLModel/myModel.keras')

images = os.listdir("assets/takenPic/")
blue = False

for i in images:
        path = 'assets/takenPic/' + i
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



im = Image.open('assets/takenPic/filename.jpg', 'r')
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