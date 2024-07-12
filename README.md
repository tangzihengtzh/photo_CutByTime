
![(A8@G_FIL 3DEEWE(1{ XTI](https://github.com/user-attachments/assets/518040f4-0a35-41ca-8f99-31dcea77be7a)
![QQ图片20240712140053](https://github.com/user-attachments/assets/5335b7d5-08fd-4054-ad2c-6ef4c781963d)
![QQ图片20240712140057](https://github.com/user-attachments/assets/dc38ac2e-4a5d-4e1b-8944-e9cbf03e17a0)

# 项目简介

这是一个基于Qt的图像处理项目，使用OpenCV库进行图像处理。该项目提供了图像显示、缩略图生成、亮度计算以及图像合成等功能。

## UI说明

该项目的用户界面通过 `mainwindow.ui` 文件定义。主要控件包括：

- **QTextEdit**: 用户输入文件夹路径的文本框。
- **QPushButton**: 执行各种操作的按钮。
- **QProgressBar**: 显示处理进度的进度条。
- **QGraphicsView**: 显示图像的视图。
- **QChartView**: 显示亮度曲线的视图。

### 主要UI操作
1. 用户在文本框中输入文件夹路径。
2. 点击相应按钮计算RGB通道的亮度曲线或合成图像。
3. 进度条显示处理进度。
4. 处理完成后，结果显示在相应的视图中。

## 运行项目

1. 确保已安装Qt和OpenCV库。
2. 在Qt Creator中打开项目文件并构建。
3. 运行项目，根据UI提示进行操作。

## 代码结构

- `mainwindow.cpp`: 包含主要的业务逻辑和事件处理函数。
- `mainwindow.ui`: 定义用户界面布局。
- `mylib.h`: 声明图像处理相关的函数。
- `SampledImageProcessor.h/cpp`: 实现图像处理的具体逻辑。

希望这份说明能帮助你理解项目的功能和使用方法。如果有任何问题，请随时联系。


# Project Overview

This is a Qt-based image processing project utilizing the OpenCV library. The project provides functions for displaying images, generating thumbnails, calculating brightness, and image synthesis.

## UI Description

The user interface of this project is defined in the `mainwindow.ui` file. The main controls include:

- **QTextEdit**: Text box for user input of the folder path.
- **QPushButton**: Buttons for executing various operations.
- **QProgressBar**: Progress bar displaying the processing progress.
- **QGraphicsView**: Views for displaying images.
- **QChartView**: Views for displaying brightness curves.

### Main UI Operations
1. The user inputs the folder path in the text box.
2. Click the corresponding button to calculate the brightness curves for RGB channels or synthesize images.
3. The progress bar shows the processing progress.
4. After processing, the results are displayed in the respective views.

## Running the Project

1. Ensure that Qt and OpenCV libraries are installed.
2. Open the project file in Qt Creator and build it.
3. Run the project and follow the UI instructions to operate.

## Code Structure

- `mainwindow.cpp`: Contains the main business logic and event handling functions.
- `mainwindow.ui`: Defines the layout of the user interface.
- `mylib.h`: Declares the functions related to image processing.
- `SampledImageProcessor.h/cpp`: Implements the specific logic for image processing.

This guide should help you understand the project's functionalities and usage. If you have any questions, feel free to contact us.
