# Homework 4

这一次作业我们将练习使用深度学习框架 [PyTorch](https://pytorch.org/)，基于该框架快速搭建一个神经模型，在 MNIST 数据集上实现手写数字识别的一整套流程，包括数据准备，模型搭建，训练、验证和测试等。

## 目录

- [设置代码仓库](#设置代码仓库)
- [手写数字识别](#手写数字识别)
    - [题目 1. 数据准备](#题目-1-数据准备)
    - [题目 2. 模型搭建](#题目-2-模型搭建)
    - [题目 3. 执行代码](#题目-3-执行代码)
    - [题目 4. 实验对比](#题目-4-实验对比)
    - [题目 5. 拓展作业](#题目-5-拓展作业)
- [作业提交要求](#作业提交要求)

## 设置代码仓库

1. 克隆仓库到本地

```bash
git clone https://gitee.com/ghgxj/Homework-4.git
```

2. 安装 PyTorch 和 TorchVision

> [https://pytorch.org/get-started/locally/](https://pytorch.org/get-started/locally/)

3. 安装其它第三方依赖库

```bash
pip install -r requirements.txt
```

## 手写数字识别

MNIST 数据集是一个广泛应用于机器学习和深度学习领域的经典数据集之一。每张图片都是 28x28 像素的灰度图像（通道数为 1），代表了 0 到 9 之间的一个手写数字。

MNIST 数据集的目标是通过机器学习算法对手写数字进行分类。这使得它成为了许多学习算法的基准测试数据集，研究人员可以利用它来比较不同模型的性能。由于 MNIST 数据集相对较小，训练速度较快，因此它也常被用于教学目的。

### 题目 1. 数据准备

克隆代码后，压缩的数据集保存在 `mnist.tar.gz` 文件中。

所以，首先我们需要解压数据集：

```bash
tar -zxvf mnist.tar.gz
```

可视化预览一下数据集中的部分样本：

![vis](/image/vis.png)

接下来，创建一个 `dataset.py` 文件来封装整个数据集。

你需要完善 `dataset.py` 中的 `__getitem__` 方法和 `__len__` 方法，这两个方法是 PyTorch 数据调用的基础。前者定义了每个数据样本的加载规则，后者返回整个数据集的长度。

### 题目 2. 模型搭建

你需要在 `model.py` 中搭建一个线性模型 `LNN` 和卷积模型 `CNN`。以供 `run.py` 调用，分别进行实验，以对比两个模型在手写数字识别上的表现（主要反映在图像分类的准确率上）。

无论是线性模型还是卷积模型，你都需要实现模型每一层的定义以及前向传播过程。并且模型输入的维度为 `(batch_size, 1, 28, 28)`，模型的输出的维度为`(batch_size, 10)`，我会在代码测试中考虑这一点。

线性模型主要使用 [nn.Linear](https://pytorch.org/docs/stable/generated/torch.nn.Linear.html) 实现，卷积模型主要使用 [nn.Conv2d](https://pytorch.org/docs/stable/generated/torch.nn.Conv2d.html) 实现。你必须保证模型上一层的输出和下一层的可接受的输入维度对齐，这样整个数据流才会打通，不至于报错。

### 题目 3. 执行代码

接下来，您需要在 `run.py` 中补全模型训练（training）、验证（validation）和测试（testing）的代码。

首先，你需要补全加载数据函数 `def load_dataset(self)` 的代码。将数据集 `dataset` 按照 `8:1:1` 的比例，随机划分为训练集 `train_set`，验证集 `val_set` 和测试集 `test_set`，随机种子请统一设置为 42。你必须调用 `torch.utils.data` 中的 [random_split](https://pytorch.org/docs/stable/data.html#torch.utils.data.random_split) 函数来划分。

**_训练_**：补全 `def train(self)` 中的训练流程，它应该包括：梯度清零、前向传播、损失计算、反向传播和参数优化。每个流程对应一行代码，你仅需填写 5 行代码。

**_验证_**：累加每个批次（batch）预测为对的图像数量 `correct` 和总的图像数量 `total`，以供验证集准确率 `accuracy` 计算。然后，保存在验证集上准确率最大的模型作为最佳模型。你需要比较 `accuracy` 和 `best_accuracy` 的大小，保存模型可以使用 `torch.save()` 函数，最佳模型的命名统一为 `best_model.pth`。

**_测试_**：补全 `def test(self)` 函数，加载最佳模型在测试集上测试。

---

完成上述代码，训练得到一个模型后。你可以使用我们实现的 3 个推理脚本：

- `inference_cli.py`：命令行推理
- `inference_gui.py`：桌面应用程序推理
- `inference_web.py`：网页在线绘图推理

![web](/image/web.png)

来体验一下机器学习和计算机视觉的魅力。

### 题目 4. 实验对比

请在 `exp.md` 中分别填写不同模型选择、优化器选择和学习率选择的实验结果对比。

### 题目 5. 拓展作业

手写数字识别是一个比较简单的任务，相信你训练的模型已经达到了一个很高的测试集准确率。但仍然会有一些失败的样例，比如图像上手写的数字是 3，模型的预测结果为 5。或者图像上手写的数字本身辨识度就很差，导致模型预测出错。我们需要明白，当数据本身就存在问题时，测试集准确率 100%也不是一个好事，说明我们的模型存在过拟合的情况。

对于拓展作业，你仅需提交一张名为 `failure.jpg` 的图片，里面包含了若干张预测失败的案例图片，需要注明标签是数字几，预测的结果是数字几。

## 作业提交要求

您需要提交 `dataset.py`、`model.py`、`run.py`、`exp.md` 以及 `failure.jpg` 5 个文件。将这 5 个文件打包为一个压缩包，并以 `学号-姓名.zip` 的格式命名，提交到网络学堂中。

不要更改任何其他文件，也不要更改函数的签名行。我们将依靠这些来保持测试的一致性。您可以自由定义任意数量的额外结构/类、函数、全局变量。不要提交任何额外的东西。

---

打分标准如下：

- 数据集：`dataset.py`（必做，总计 7 分）

| 类方法          | 分数 |
| --------------- | ---- |
| \_\_len\_\_     | 2    |
| \_\_getitem\_\_ | 5    |

- 模型：`model.py`（必做，总计 10 分）

| 类  | 分数 |
| --- | ---- |
| LNN | 5    |
| CNN | 5    |

- 执行器：`run.py`（必做，总计 10 分）

| 类方法       | 分数 |
| ------------ | ---- |
| load_dataset | 2    |
| 训练         | 3    |
| 验证         | 2    |
| 测试         | 3    |

- 实验对比：`exp.md`（必做，总计 20 分）

| 对比项 | 分数 |
| ------ | ---- |
| 模型   | 10   |
| 优化器 | 5    |
| 学习率 | 5    |

- 拓展作业：`failure.jpg`（选做，总计 3 分）