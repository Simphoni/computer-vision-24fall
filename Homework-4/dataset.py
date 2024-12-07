import torch
from torch.utils.data import Dataset
from torchvision import transforms
from PIL import Image
import os
import matplotlib.pyplot as plt


class CustomDataset(Dataset):
    def __init__(self, root_dir, transform=None):
        self.root_dir = root_dir
        self.transform = transform
        self.data = self.load_data()

    def load_data(self):
        data = []
        for class_label in range(10):
            class_path = os.path.join(self.root_dir, str(class_label))
            for filename in os.listdir(class_path):
                img_path = os.path.join(class_path, filename)
                data.append((img_path, class_label))
        return data

    def __len__(self):
        # TODO：返回数据集的总长度length。你应该用只用1行代码搞定。

        # 在这里编写你的代码
        length = len(self.data)

        return length

    def __getitem__(self, idx):
        # TODO：返回每个图片image和标签label对，如果transform不为None，
        # 应该为返回的image应用transform。image的维度应该为（1,28,28），
        # label 应该是0-9之间的一个整数，我们会在测试代码中考虑这两点。

        # 在这里编写你的代码
        img_path, label = self.data[idx]
        image = Image.open(img_path)
        # convert to tensor
        if self.transform is not None:
            image = self.transform(image)
        else:
            image = transforms.ToTensor()(image)

        return image, label


def visualize_dataset(dataset):
    # Dictionary to store images for each class
    class_images = {i: [] for i in range(10)}

    # Collect 10 images for each class
    for image, label in dataset:
        if len(class_images[label]) < 10:
            class_images[label].append(image)

    # Display images in a 10x10 grid
    fig, axes = plt.subplots(
        10, 10, figsize=(10, 10), subplot_kw={"xticks": [], "yticks": []}
    )

    for i in range(10):
        for j in range(10):
            axes[i, j].imshow(class_images[i][j][0], cmap="gray")
            axes[i, j].axis("off")
    plt.savefig("vis.png", bbox_inches="tight")
    plt.show()


if __name__ == "__main__":
    # Testing
    transform = transforms.Compose([transforms.ToTensor()])
    dataset = CustomDataset(root_dir="mnist", transform=transform)
    assert len(dataset) == 70000
    for image, label in dataset:
        assert image.shape == (1, 28, 28)
        assert label in range(10)
        break
    # visualize_dataset(dataset)
