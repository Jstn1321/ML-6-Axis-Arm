import json
import os
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

json_path = os.path.join(os.path.dirname(__file__), 'assets/boxCoords.json')
with open(json_path, "r") as file:
    data = json.load(file)

blueCoord = 0
greenCoord = 0
bluebox = data["bluebox"]
greenbox = data["greenbox"]
bluex = 0
bluey = 0
greenx = 0
greeny = 0

#in x y x y
if bluebox == True:
    blueCoord = data["blueCoord"]
    bluex = ((blueCoord[2] - blueCoord[0])/2) + blueCoord[0]
    bluey = ((blueCoord[3] - blueCoord[1])/2) + blueCoord[1]
if greenbox == True:
    greenCoord = data["greenCoord"]
    greenx = ((greenCoord[2] - greenCoord[0])/2) + greenCoord[0]
    greeny = ((greenCoord[3] - greenCoord[1])/2) + greenCoord[1]

print(blueCoord)
print(greenCoord)

plt.title("Box Image")
plt.xlabel("X pixel scaling")
plt.ylabel("Y pixels scaling")
plt.plot(bluex, bluey, marker='v', color="purple")
plt.plot(greenx, greeny, marker='v', color="yellow")

image = mpimg.imread(os.path.join(os.path.dirname(__file__), "assets/takenPic/filename.jpg"))
plt.imshow(image)
plt.show()