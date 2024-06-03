## Funny Json Explorer: 一个命令行的json文件可视化工具

​		软件工程作业：一个读取json文件形成数据结构，再将其按照指定风格输出到终端的c++程序。

​		其中读取json文件的部分使用到了github的开源项目[nlohmann/json: JSON for Modern C++ (github.com)](https://github.com/nlohmann/json) 。其余的数据结构见目录`doc`下的设计文档。

​		由于使用了抽象工厂模式，因此只需添加新的继承类，在抽象工厂中添加新的继承类构造方法，即可方便地添加新的风格和图标族。详情请见`doc`下的设计文档。

### 编译

以下批处理文件编译该项目为可执行文件为`fje.exe`，并输出到`build`目录下：

```shell
.\build.bat
```

以下批处理文件编译并将可执行文件输出到`release`目录下，并直接将fje.exe写入到用户的环境变量，需要以管理员权限运行：

```
.\install.bat
```

### 运行

如果运行了`install.bat`，那么启动powershell，输入：

```
fje -f [FILEPATH] -s [N] -i [N]
```

如果仅运行了`build.bat`，那么在`build`目录下启动`powershell`，输入：

```
.\fje.exe -f [FILEPATH] -s [N] -i [N]
```

其中`[FILEPATH]`为json文件路径，`[N]`为正整数；`-s`代表绘制风格，1代表树形，2代表矩形；`-i`代表图标族，默认取值为`1`或`2`。在添加新的风格或图标族后，上述取值可以继续增加。