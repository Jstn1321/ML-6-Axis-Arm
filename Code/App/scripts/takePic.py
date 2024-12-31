import cv2

def capture_image():
    # Open camera
    camera = cv2.VideoCapture(0)
    if not camera.isOpened():
        return "Unable to access the camera."
    
    # Read a frame
    ret, frame = camera.read()
    if ret:
        resized_frame = cv2.resize(frame, (300, 300))
        # Save the resized frame as an image
        cv2.imwrite('assets/takenPic/filename.jpg', resized_frame)
    
    # Release camera
    camera.release()

capture_image()