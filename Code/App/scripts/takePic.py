import cv2
import sys
import os


def capture_image():
    # Open camera
    camera = cv2.VideoCapture(1)
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
sys.stdout.flush()