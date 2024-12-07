import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
from inference import load_and_preprocess_image, inference
from model import CNN
import torch


class InferenceApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Handwritten Digit Recognition")

        self.create_widgets()

    def create_widgets(self):
        # Create GUI components
        self.label = tk.Label(self.root, text="Select an image for prediction:")
        self.label.pack(pady=10)

        self.image_label = tk.Label(self.root)
        self.image_label.pack(pady=10)

        self.browse_button = tk.Button(
            self.root, text="Browse", command=self.browse_image
        )
        self.browse_button.pack(pady=10)

        self.predict_button = tk.Button(self.root, text="Predict", command=self.predict)
        self.predict_button.pack(pady=10)

        self.result_label = tk.Label(self.root, text="")
        self.result_label.pack(pady=10)

    def browse_image(self):
        file_path = filedialog.askopenfilename(
            filetypes=[("Image files", "*.png;*.jpg;*.jpeg")]
        )
        if file_path:
            self.display_image(file_path)

    def display_image(self, file_path):
        img = Image.open(file_path)
        img.thumbnail((300, 300))
        img = ImageTk.PhotoImage(img)
        self.image_label.config(image=img)
        self.image_label.image = img

        self.selected_image = file_path
        self.result_label.config(text="")

    def predict(self):
        if hasattr(self, "selected_image"):
            probabilities, predicted_class = inference(self.selected_image)

            # Display the result
            result_text = (
                f"Predicted Class: {predicted_class}\nProbabilities: {probabilities}"
            )
            self.result_label.config(text=result_text)
        else:
            self.result_label.config(text="Please select an image first.")


if __name__ == "__main__":
    root = tk.Tk()
    app = InferenceApp(root)
    root.mainloop()
