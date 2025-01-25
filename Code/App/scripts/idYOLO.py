from ultralytics import YOLO
import os
import json

# Load a model
model_path = os.path.join(os.path.dirname(__file__), 'assets/MLModel/best.pt')
model = YOLO(model_path, verbose=False)  # load a pretrained model (recommended for training)

# Use the model
results_path = os.path.join(os.path.dirname(__file__), 'assets/takenPic/filename.jpg')
results = model(results_path, save=True, verbose = False)  # predict on an image
bluebox = False
greenbox = False
boxids = []
conf = []
for result in results:
    for box in result.boxes:
        confidence = box.conf[0].item()
        label = box.cls[0].item()            
        boxids.append(label)
        conf.append(confidence)
        if box.cls[0].item() == 0.0:
            blueCoord = box.xyxy[0].tolist()
            bluebox = True
        if box.cls[0].item() == 1.0:
            greenCoord = box.xyxy[0].tolist()
            greenbox = True
if len(boxids) == 1:
    if boxids[0] == 1.0:
        boxname = "green box"
        conf[0] = int(conf[0] * 100)
        conf = list(map(str,conf))
        print("I think this is a " + boxname + " with a confidence of " + conf[0]) + "%."
        data = {
            "greenbox": greenbox,
            "greenCoord": greenCoord
        }
    if boxids[0] == 0.0:
        boxname = "blue box"
        conf[0] = int(conf[0] * 100)
        conf = list(map(str,conf))
        print("I think this is a " + boxname + " with a confidence of " + conf[0]) + "%."
        data = {
            "bluebox": bluebox,
            "blueCoord": blueCoord,
        }

else:
    for i in range(0,len(conf)):
        conf[i] = int(conf[i] * 100)
    boxname = []
    if boxids[0] == 1.0:
        boxname.append("green box")
        boxname.append("blue box")
    else:
        boxname.append("blue box")
        boxname.append("green box")
    conf = list(map(str,conf))

    print("I see two boxes, a green and blue box. I am " + conf[0] + "% sure that the first box is a " + boxname[0] + " and " + conf[1] + "% sure that the second box is a " + boxname[1] + ".")



    data = {
        "bluebox": bluebox,
        "greenbox": greenbox,
        "blueCoord": blueCoord,
        "greenCoord": greenCoord
    }
json_path = os.path.join(os.path.dirname(__file__), 'assets/boxCoords.json')
with open(json_path, "w") as file:
    json.dump(data,file,indent=4)