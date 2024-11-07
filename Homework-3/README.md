# Homework 3

这一次作业我们将练习使用Python构建一个图像特征匹配器，从简单的卷积操作开始，然后进行兴趣点检测和描述符提取，最后基于此实现全景图像拼接器等。

## 目录

- [设置代码仓库](#设置代码仓库)
- [图像特征提取与匹配](#图像特征提取与匹配)
- [全景图像拼接](#全景图像拼接)
- [作业提交要求](#作业提交要求)

## 设置代码仓库

1. 克隆仓库到本地

```bash
git clone https://gitee.com/ghgxj/Homework-3.git
```

2. 安装 IPython/Jupyter

```
http://jupyter.org/install.html
```

3. 安装其它第三方依赖库

```bash
pip install -r requirements.txt
```

## 图像特征提取与匹配

启动Jupyter并打开`Project1.ipynb`。

在本项目中，您将构建一个图像特征匹配器，从简单的卷积运算开始，然后进行兴趣点检测和描述符提取。一旦你有一个基本的功能匹配器工作，尝试一些改进并记录你的结果。

具体作业要求参见`Project1.ipynb`。

## 全景图像拼接

启动Jupyter并打开`Project2.ipynb`。

在本项目中，你将实现一个全景图像拼接器。这将建立在项目 1 中开发的兴趣点和描述符的基础上。您将首先通过 RANSAC 进行几何过滤，然后估计成对旋转并将其链接在一起以对齐全景图。当您有一个基本的缝合器工作时，使用更好的对齐、混合或其他新功能来改进它，并记录您的发现。

具体作业要求参见`Project2.ipynb`。

## 作业提交要求

将修改后的整个代码库打包，并以 `学号-姓名.zip` 的格式命名，提交到网络学堂中。

不要更改任何其他文件，也不要更改函数的签名行。我们将依靠这些来保持测试的一致性。您可以自由定义任意数量的额外结构/类、函数、全局变量。不要提交任何额外的东西。

---

打分标准如下：

1. 图像特征提取与匹配

- 卷积和图像滤波，5分
- 兴趣点提取器，5分
- 描述符和匹配，5分
- 测试和改进特征匹配，5分
- 一致性测试，3分

2. 全景图像拼接

- 相似度求解器，4分
- RANSAC环路，3分
- 旋转估计，3分
- 全景对齐，3分
- 测试和改进全景拼接器，4分