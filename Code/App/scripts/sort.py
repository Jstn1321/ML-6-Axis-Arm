import numpy as np
import os
import subprocess
import sys
from PIL import Image
import cv2
from identify import blue
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import sendInvKine

im = Image.open(os.path.join(os.path.dirname(__file__), "assets/takenPic/filename.jpg"), 'r')
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
        #print(imgaB)
        where_list = imgaB.index(max(imgaB))
        where_list = where_list + 1
        #print(where_list)

row = (where_list/300)//1
temp = where_list - row
column = where_list - ((row*300)+1)
row = row + 7
column+= 10

print("X: " + column)
print("Y " + row)

sendInvKine.sendInvKineToArd()

plt.title("Box Image")
plt.xlabel("X pixel scaling")
plt.ylabel("Y pixels scaling")
plt.plot(column, row, marker='v', color="purple")

image = mpimg.imread(os.path.join(os.path.dirname(__file__), "assets/takenPic/filename.jpg"))
plt.imshow(image)
plt.show()