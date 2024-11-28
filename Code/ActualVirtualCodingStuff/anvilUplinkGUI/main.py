import anvil.server
import anvil.media
import imageio
from PIL import Image  # No need to import ImageResampling separately
import numpy as np

anvil.server.connect("server_GN3CNHVVCYPXNCHUHZYSDK7O-PBVHIQDAESJ7MGYC")

@anvil.server.callable
def take_Picture():
    filename = 'bog/liveTest/filename.jpg'  # Fixed filename

    # Use imageio with ffmpeg for video capture
    camera = imageio.get_reader('<video0>', 'ffmpeg')

    # Capture one frame
    image = camera.get_next_data()

    # Convert numpy array to PIL Image
    image = Image.fromarray(image.astype('uint8'), 'RGB')

    # Resize the image to 300x300 using LANCZOS (high-quality)
    image = image.resize((352, 288), Image.Resampling.LANCZOS)

    # Save the image
    image.save(filename)

    return anvil.media.from_file("C:/Users/iamaa/PycharmProjects/anvilUplinkGUI/bog/liveTest/filename.jpg", "image/jpg")

# Keep the connection alive
anvil.server.wait_forever()
