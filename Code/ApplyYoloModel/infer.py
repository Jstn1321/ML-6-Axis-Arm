import onnxruntime as ort
import numpy as np

# Load ONNX model
model_path = "C:\\Nerd Projects\\RobotArmProject\\Code\\YOLOModels\\v11\\yolo11n.onnx"  # Replace with your ONNX model path
session = ort.InferenceSession(model_path)

# Display model input and output details
input_details = session.get_inputs()
output_details = session.get_outputs()

print("Model Input Details:")
for inp in input_details:
    print(f"Name: {inp.name}, Shape: {inp.shape}, Type: {inp.type}")

print("\nModel Output Details:")
for out in output_details:
    print(f"Name: {out.name}, Shape: {out.shape}, Type: {out.type}")

# Prepare dummy input data (adjust shape and type to match the model)
input_name = input_details[0].name
input_shape = input_details[0].shape
input_data = np.random.randn(*input_shape).astype(np.float32)

# Run inference
output_name = output_details[0].name
outputs = session.run([output_name], {input_name: input_data})

# Print results
print("\nInference Output:")
print(outputs)
