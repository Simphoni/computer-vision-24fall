import torch.nn as nn
import torch


class LNN(nn.Module):
    def __init__(self):
        super(LNN, self).__init__()
        # TODO: 全部用线性层来定义模型的结构，包括输入层、隐藏层和输出层

        channels = [28 * 28, 1024, 384, 128, 10]
        fc = []
        for i in range(len(channels) - 1):
            fc.append(nn.Linear(channels[i], channels[i + 1]))
        self.fc = fc

        # 在这里编写你的代码

    def forward(self, x):
        # TODO: 实现前向传播过程。若输入值x的维度为(batch_size, 1, 28, 28)，那么返回值y的维度必须为(batch_size, 10)，我们会在代码测试中考虑这一点。
        
        batch_size = x.size(0)

        # 在这里编写你的代码
        tmp = x.view(batch_size, -1)
        for layer in self.fc:
            tmp = layer(tmp)
        y = tmp
        y = y.view(batch_size, 10)

        return y


class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        # TODO: 定义一个主体结构为卷积的神经网络模型

        self.conv1 = nn.Conv2d(1, 64, 3, stride=1, padding=1) # 28x28 -> 28x28
        self.conv2 = nn.Conv2d(64, 64, 3, stride=2, padding=1) # 28x28 -> 14x14
        self.conv3 = nn.Conv2d(64, 32, 3, stride=2, padding=1) # 14x14 -> 7x7
        self.conv4 = nn.Conv2d(32, 16, 3, stride=2, padding=1) # 7x7 -> 4x4
        self.fc = nn.Linear(4 * 4 * 16, 10)

        # 在这里编写你的代码

    def forward(self, x):
        # TODO: 实现前向传播过程。若输入值x的维度为(batch_size, 1, 28, 28)，那么返回值y的维度必须为(batch_size, 10)，我们会在代码测试中考虑这一点。

        batch_size = x.size(0)
        y = x
        y = self.conv1(y)
        y = self.conv2(y)
        y = self.conv3(y)
        y = self.conv4(y)
        y = y.view(batch_size, -1)
        y = self.fc(y)
        y = y.view(batch_size, 10)

        # 在这里编写你的代码

        return y


if __name__ == "__main__":
    batch_size = 1

    # Testing for LNN
    model = LNN()
    x = torch.randn(batch_size, 1, 28, 28)
    y = model(x)
    assert y.shape == (batch_size, 10)

    # Testing for CNN
    model = CNN()
    x = torch.randn(batch_size, 1, 28, 28)
    y = model(x)
    assert y.shape == (batch_size, 10)
