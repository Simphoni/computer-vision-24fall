import torch
from torchvision import transforms
from PIL import Image
from model import CNN


def load_and_preprocess_image(image_path):
    transform = transforms.Compose(
        [transforms.ToTensor(), transforms.Resize((28, 28))]
    )  # Resize to 28x28
    image = Image.open(image_path).convert("L")  # Convert to grayscale
    image = transform(image)
    return image


def inference(image_path):
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    # Load the trained model
    model = CNN().to(device)
    model.load_state_dict(torch.load("best_model.pth"))
    model.eval()

    # Load and preprocess the input image
    input_image = load_and_preprocess_image(image_path)
    input_image = input_image.unsqueeze(0).to(device)

    # Perform inference
    with torch.no_grad():
        output = model(input_image)

    # Get predicted class probabilities
    probabilities = torch.nn.functional.softmax(output[0], dim=0)

    # Get the predicted class
    _, predicted_class = torch.max(output, 1)

    return probabilities.cpu().numpy(), predicted_class.item()


if __name__ == "__main__":
    image_path = r"mnist\0\test_13.png"
    probabilities, predicted_class = inference(image_path)
    print(f"Predicted Probabilities: {probabilities}")
    print(f"Predicted Class: {predicted_class}")
