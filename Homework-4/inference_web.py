from flask import Flask, render_template, request, jsonify
from PIL import Image
import torch
from torchvision import transforms
from model import CNN
import io
import base64
import numpy as np

app = Flask(__name__)

# Load the pre-trained model
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = CNN().to(device)
model.load_state_dict(torch.load('best_model.pth'))
model.eval()

# Transformations for the input image
transform = transforms.Compose([
    transforms.Grayscale(num_output_channels=1),
    transforms.Resize((28, 28)),
    transforms.ToTensor()
])

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/predict', methods=['POST'])
def predict():
    if 'data' not in request.json:
        return jsonify({'error': 'No data received'})

    try:
        # Decode base64 image data
        image_data = base64.b64decode(request.json['data'].split(',')[1])
        img = Image.open(io.BytesIO(image_data))
        img = transform(img).unsqueeze(0).to(device)

        with torch.no_grad():
            output = model(img)
            probabilities = torch.softmax(output, dim=1)[0].cpu().numpy()
            predicted_class = int(torch.argmax(output, dim=1))

        # Convert NumPy float32 values to Python native types
        probabilities = probabilities.tolist()

        # Prepare bar chart data
        classes = [str(i) for i in range(10)]
        bar_data = [{'class': c, 'probability': round(probabilities[i], 4)} for i, c in enumerate(classes)]

        return jsonify({'class': predicted_class, 'probabilities': bar_data})
    except Exception as e:
        return jsonify({'error': f'Error processing image: {str(e)}'})

if __name__ == '__main__':
    app.run(debug=True)
