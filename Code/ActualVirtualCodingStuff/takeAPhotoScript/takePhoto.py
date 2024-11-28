import anvil.server
import anvil.media
import imageio
from PIL import Image

anvil.server.connect("server_GN3CNHVVCYPXNCHUHZYSDK7O-PBVHIQDAESJ7MGYC")


@anvil.server.callable
def take_Picture():
    filename = 'bog/liveTest/filename.jpg'  # Fixed filename

    # Initialize the camera (0 is the default camera)
    camera = imageio.get_reader('<video0>')

    # Capture one frame
    image = camera.get_next_data()

    # Convert the image array to a PIL Image
    pil_image = Image.fromarray(image)

    # Resize the image to 300x300
    resized_image = pil_image.resize((300, 300))

    # Save the resized image
    resized_image.save(filename)

    return anvil.media.from_file("C:/Users/iamaa/PycharmProjects/takeAPhotoScript/bog/liveTest/filename.jpg",
                                 "image/jpg")


# Keep the connection alive
anvil.server.wait_forever()
