import json
import os
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import sendInvKine
import math

json_path = os.path.join(os.path.dirname(__file__), 'assets/boxCoords.json')
with open(json_path, "r") as file:
    data = json.load(file)

blueCoord = 0
greenCoord = 0
#bluebox = data["bluebox"]
#greenbox = data["greenbox"]
bluex = 0
bluey = 0
greenx = 0
greeny = 0

#in x y x y
if data.get("bluebox"):
    blueCoord = data["blueCoord"]
    bluex = ((blueCoord[2] - blueCoord[0])/2) + blueCoord[0]
    bluey = ((blueCoord[3] - blueCoord[1])/2) + blueCoord[1]
if data.get("greenbox"):
    greenCoord = data["greenCoord"]
    greenx = ((greenCoord[2] - greenCoord[0])/2) + greenCoord[0]
    greeny = ((greenCoord[3] - greenCoord[1])/2) + greenCoord[1]

print(blueCoord)
print(greenCoord)
#1cm is roughly 13-14px for 300x300 image and with the stand
#sendInvKine.sendInvKineToArd([0.4,0.0,0.2])
#z,x,y
print(str(bluex) + " , " + str(bluey)+ " , " + str(greenx)+ " , " + str(greeny))

zoffset = 0.25

if (data.get("greenbox")):
    globalgx = 150 - greenx
    globalgx = (globalgx / 14) * math.pow(10, -2)
    globalgy = 300 - greeny
    globalgy = (globalgy / 14) * math.pow(10, -2)
    globalgy = globalgy + zoffset
    sendInvKine.sendInvKineToArd([globalgy,globalgx,0.2], 0)
    print(str(globalgx) + " , " + str(globalgy))
    
    

if (data.get("bluebox")):
    globalbx = 150 - bluex
    globalbx = (globalbx / 14) * math.pow(10, -2)
    globalby = 300 - bluey + zoffset
    globalby = (globalby / 14) * math.pow(10, -2)
    print(str(globalbx) + " , " + str(globalby))
    sendInvKine.sendInvKineToArd([globalby,globalbx,0.2], 1)

"""
plt.title("Box Image")
plt.xlabel("X pixel scaling")
plt.ylabel("Y pixels scaling")
if data.get("bluebox"):
    plt.plot(bluex, bluey, marker='v', color="purple")
if data.get("greenbox"):
    plt.plot(greenx, greeny, marker='v', color="yellow")

image = mpimg.imread(os.path.join(os.path.dirname(__file__), "assets/takenPic/filename.jpg"))
plt.imshow(image)
plt.show()
"""