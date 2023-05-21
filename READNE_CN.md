
# PicoTK

该库提供了一个基于 PicoGL 的轻量级 OpenGL 框架。

---

## 兼容性

该库已在 esp32-wrover-b 上进行了测试。

---

## 安装

1. 从仓库下载库。
2. 将头文件和源代码文件添加到您的项目目录中。

---

## 使用方法

1. 实现自己的初始化函数和更新逻辑的更新函数。
2. 调用`ui_init()`函数以您自己的初始化函数和更新函数作为参数来初始化用户界面。
3. 调用`ui_loop()`函数进入事件循环并处理用户界面事件。
4. 调用`ui_end()`函数释放 UI 使用的资源。

---

## 示例代码

请参阅 example 文件夹。

---

## API 参考

***ui_init(void (*init_fn)(void), int (*update_fn)(void))***

使用您自己的初始化函数和更新函数初始化用户界面。如果成功返回 0，否则返回 -1。

参数：

- `init_fn`：指向您自己的初始化函数的函数指针。
- `update_fn`：指向您自己的更新函数的函数指针。

***ui_loop()***

进入 UI 更新的的主要函数。

***ui_end()***

释放 UI 使用的资源。

***tkSwapBuffers()***

交换缓冲区以更新屏幕。

---

## 引用/引述

1. [kaaass 的博客](https://blog.kaaass.net/archives/1340).
2. [PicoGL](https://www.pico.net/kb/picogl). Pico.