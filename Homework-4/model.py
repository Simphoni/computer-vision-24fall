import torch.nn as nn
import torch


class LNN(nn.Module):
    def __init__(self):
        super(LNN, self).__init__()
        # TODO: 全部用线性层来定义模型的结构，包括输入层、隐藏层和输出层

        # 在这里编写你的代码

    def forward(self, x):
        # TODO: 实现前向传播过程。若输入值x的维度为(batch_size, 1, 28, 28)，那么返回值y的维度必须为(batch_size, 10)，我们会在代码测试中考虑这一点。

        # 在这里编写你的代码

        return y


class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        # TODO: 定义一个主体结构为卷积的神经网络模型

        # 在这里编写你的代码

    def forward(self, x):
        # TODO: 实现前向传播过程。若输入值x的维度为(batch_size, 1, 28, 28)，那么返回值y的维度必须为(batch_size, 10)，我们会在代码测试中考虑这一点。

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
