import numpy as np
import os
import subprocess
import sys
from PIL import Image
import cv2
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import sendInvKine
import tensorflow as tf
import numpy as np
from tensorflow.keras.optimizers import RMSprop
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.utils import load_img, img_to_array

def capture_image():
    # Open camera
    camera = cv2.VideoCapture(0)
    if not camera.isOpened():
        return "Unable to access the camera."
    
    # Read a frame
    ret, frame = camera.read()
    if ret:
        resized_frame = cv2.resize(frame, (300, 300))
        image_path = os.path.join(os.path.dirname(__file__), 'assets/takenPic/filename.jpg')
        cv2.imwrite(image_path, resized_frame)
        print("Saved image")
    # Release camera
    camera.release()

capture_image()

model_path = os.path.join(os.path.dirname(__file__), 'assets/MLModel/myModel.keras')
model = tf.keras.models.load_model(model_path)
image_path = os.path.join(os.path.dirname(__file__), "assets/takenPic/")
blue = False
images = os.listdir(image_path)

for i in images:
        
        path = image_path + i
        img = load_img(path, target_size=(300, 300))
        x = img_to_array(img)
        x /= 255

        x = np.expand_dims(x, axis=0)

        images = np.vstack([x])
        classes = model.predict(images, batch_size=1, verbose = 0)
        #print(classes[0])
        if classes[0]>0.5:
            #print(i + " is a green box")
            print("This is a green box!")
            sys.stdout.flush()
            blue = False
        else:
            #print(i + " is a blue box")
            print("This is a blue box!")
            sys.stdout.flush()
            blue = True

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



sys.stdout.flush()