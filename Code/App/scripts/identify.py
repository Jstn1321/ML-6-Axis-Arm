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
