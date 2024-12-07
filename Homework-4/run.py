import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, random_split
from torchvision import transforms
from dataset import CustomDataset
from model import LNN, CNN


class Runner:
    def __init__(
        self,
        # Setting for data
        dataset_root: str = "mnist",     # Root directory of the dataset
        batch_size: int = 32,            # Batch size of dataloader

        # Setting for model
        model_type: str = "CNN",         # Type of model (e.g., CNN)

        # Setting for training
        num_epochs: int = 10,            # Number of epochs to train
        optimizer_type: str = "Adam",    # Type of optimizer for training (e.g., Adam)
        learning_rate: float = 1e-3,     # Learning rate for optimizer
    ):
        self.dataset_root = dataset_root
        self.batch_size = batch_size

        self.model_type = model_type

        self.num_epochs = num_epochs
        self.optimizer_type = optimizer_type
        self.learning_rate = learning_rate

        self.device = torch.device(
            "cuda" if torch.cuda.is_available() else "cpu"
        )

    def load_dataset(self):
        # Define transformations for the dataset
        transform = transforms.Compose([transforms.ToTensor()])

        # Initialize CustomDataset with specified root directory and transformations
        dataset = CustomDataset(
            root_dir=self.dataset_root, 
            transform=transform,
        )

        # TODO：将数据集 `dataset` 按照 `8:1:1` 的比例，
        # 随机划分为训练集 `train_set`，验证集 `val_set` 和测试集 `test_set`。
        # 随机种子请设置为42，你必须调用 `torch.utils.data` 中的 `random_split` 函数来划分。

        # 在这里编写你的代码

        # Create DataLoader instances for train, validation, and test sets
        self.train_loader = DataLoader(
            train_set, batch_size=self.batch_size, shuffle=True
        )
        self.val_loader = DataLoader(val_set, batch_size=self.batch_size)
        self.test_loader = DataLoader(test_set, batch_size=self.batch_size)

    def initialize_model(self):
        # Initialize model
        if self.model_type == "LNN":
            self.model = LNN().to(self.device)
        elif self.model_type == "CNN":
            self.model = CNN().to(self.device)
        else:
            raise ValueError(
                "Unsupported model type. Supported types are 'LNN' and 'CNN'."
            )

        # Define criterion (loss function) for training
        self.criterion = nn.CrossEntropyLoss()

        # Define optimizer with specified learning rate
        if self.optimizer_type == "Adam":
            self.optimizer = optim.Adam(
                self.model.parameters(), lr=self.learning_rate)
        elif self.optimizer_type == "SGD":
            self.optimizer = optim.SGD(
                self.model.parameters(), lr=self.learning_rate)
        else:
            raise ValueError(
                "Unsupported optimizer type. Supported types are 'Adam' and 'SGD'."
            )

    def train(self):
        best_accuracy = 0.0

        # Training loop over epochs
        for epoch in range(self.num_epochs):
            self.model.train()

            # Iterate over batches in training DataLoader
            for images, labels in self.train_loader:
                images, labels = images.to(self.device), labels.to(self.device)
                
                # TODO：补全训练流程，它应该包括：梯度清零、前向传播、损失计算、反向传播和参数优化。

                # 在这里编写你的代码（你应该补全5行代码）

            # Validation
            self.model.eval()
            correct = 0 # 预测为对的图像数量
            total = 0 # 总的图像数量

            # Iterate over batches in validation DataLoader
            with torch.no_grad():
                for images, labels in self.val_loader:
                    images, labels = images.to(
                        self.device), labels.to(self.device)
                    
                    # TODO：累加每个批次（batch）预测为对的图像数量 `correct` 和总的图像数量 `total`，以供下方的验证集准确率 `accuracy` 计算。

                    # 在这里编写你的代码

            # Compute validation accuracy
            accuracy = correct / total # 预测准确率
            print(
                f"Epoch {epoch+1}/{self.num_epochs}, Validation Accuracy: {accuracy}")

            # TODO：保存验证集准确率最大的模型作为最佳模型。保存模型可以使用 `torch.save()` 函数，最佳模型的命名统一为 `best_model.pth`。

            # 在这里编写你的代码

    def test(self):
        # TODO：加载最佳模型在测试集上进行测试。

        # 在这里编写你的代码
        
        print(f"Test Accuracy: {test_accuracy}")


if __name__ == "__main__":·
    # Initialize Runner
    trainer = Runner()

    # Load dataset
    trainer.load_dataset()

    # Initialize model, loss, and optimizer
    trainer.initialize_model()

    # Train the model
    trainer.train()

    # Test the model
    trainer.test()
