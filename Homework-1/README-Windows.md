# Windows 安装指南

1. 启动 Visual Studio 2017。
2. 点击 "文件" -> "从现有代码创建新项目"。
3. 在欢迎界面上确保选择了 Visual C++。
4. 点击 "下一步"。
5. 在下一个界面上。
6. 在 "项目文件位置" 中添加 src 文件夹的路径。
7. 例如：D:\Projects\XXX\CV\HW1\src。
8. 在 "项目名称" 中给一个名字（例如 CV_HW1）。
9. 勾选 "从这些文件夹添加文件到项目"。
10. 勾选 "添加子文件夹"。
11. 勾选 "在解决方案资源管理器中显示所有文件"。
12. 点击 "下一步"。
13. 在指定项目设置中。
14. 勾选使用 Visual Studio。
15. 在项目类型中选择控制台应用程序项目。
16. 点击 "下一步"。
17. 在指定调试配置中点击 "下一步"。
18. 在指定发布配置中勾选与调试配置相同。
19. 点击 "完成"。

您应该在解决方案资源管理器中看到所有的源文件和头文件。
双击 `test.c` 可以在源代码窗口中查看源代码。
`test0.cpp` 中有 `main()` 函数。
在顶部菜单的配置框中选择 Debug X64/x86。

在右侧的解决方案资源管理器窗口中
右键点击 <项目名称>，然后点击 "生成"。
您的项目应该能够在没有错误的情况下构建。

构建输出窗口应该显示：

```bash
1>UW_CS576_HW1.vcxproj -> D:\Projects\MySandBox\UW_CS576\HW1\src\x64\Debug\UW_CS576_HW1.exe
========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========

You can Build the Release Version also by choosing
Release   X64/x86
Right Click on the <Project Name> and Click Build
Your project should build without errors

1>UW_CS576_HW1.vcxproj -> D:\Projects\MySandBox\UW_CS576\HW1\src\x64\Release\UW_CS576_HW1.exe
========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========
```
