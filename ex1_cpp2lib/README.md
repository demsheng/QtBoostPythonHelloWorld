## ex1_cpp2lib
2021-01-29

- 作者：李长圣
- 邮箱：sheng0619@163.com
- 功能：演示在 `qtcreator` 中编译 `boost.python` 程序为动态链接库`hello.dll`，在python中调用该库。
- 支持 `window10`  系统

1. 使用 `qtcreator` 打开 `ex1.pro` 编译, 将在 `.\build-ex1-Desktop_Qt_5_12_9_MSVC2017_64bit-Debug\debug`中生成 `hello.dll`
2. 将 `hello.dll` 更名为 `hello.pyd` , 
3. 打开 `cmd` ，输入python导入 `hello.pyd`
    注意配置python的环境变量
    ```
    Microsoft Windows [版本 10.0.18363.1316]
    (c) 2019 Microsoft Corporation。保留所有权利。

    F:\>cd F:\MyProgram\QtProject\QtBoostPythonHelloWorld\build-ex1-Desktop_Qt_5_12_9_MSVC2017_64bit-Debug\debug

    F:\MyProgram\QtProject\QtBoostPythonHelloWorld\build-ex1-Desktop_Qt_5_12_9_MSVC2017_64bit-Debug\debug>python
    Python 3.9.1 (tags/v3.9.1:1e5d33e, Dec  7 2020, 17:08:21) [MSC v.1927 64 bit (AMD64)] on win32
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import hello
    >>> print(hello.greet())
    hello,world
    ```


## 编译boost.python参考 [Boost::Python的安装与调用教程](https://blog.csdn.net/u011501388/article/details/83142164)

Boost::Python库是pyhon和c++相互交互的框架，可以在Python中调用C++的类和方法，也可以让C++调用Python的类和方法。

Python自身提供了一个Python/C++ API用来实现Python和C++的交互。Boost::Python是Python/C++ API的包装，所以用起来更简单一些。

Python对一个动态类型的语言，C++是一个静态类型的语言，对于Python中的变量类型，Boost.Python都有相应的类对应，他们都是boost::python::object的子类。boost::python::object 包装了PyObject *, 通过这种方式C++可以平滑的操作Python对象。Boost.Python的主要目标既保持Python的编程风格同时又提供C++和Python的双向映射。

Boost::Python库让C++和Python几乎无缝结合，是Boost库的一个功能。 
用Boost::Python库，能快速、容易地将C++输出到Python，使得Python接口和C++接口非常像。它被设计成尽可能贴近你的C++设计。大多数情况下，你不需要修改C++类就能在Boost.Python中使用它。系统会简单地映射你的C++类和函数到Python。Boost::Python的这种绑定，是纯C++实现的，除了编辑器和编译器你什么别的都不需要。

具体详情可访问Boost主页，及关于Boost::Python的使用教程。下面是具体的关于Boost::Python的安装及使用示例教程。本人的机器环境为：Win7 64位，VS2015，下载的最新版本的Boost Library Version 1.68.0。

关于Boost::Python的安装步骤：

1. 到Boost官网下载最新版本的Boost Library；

2. 打开VS Developer Command Prompt命令行，定位到Boost解压后的文件夹，在命令行执行booststrap.bat，将在文件夹下生  成 b2.exe及bjam.exe和project-config.jam等文件，如下图所示：  
    其中project-config.jam文件不需要修改，保持默认即可，其内容如下：
    ```
    import option ;
    using msvc ;
    option.set keep-going : false ;
    ```
    而user-config.jam文件需要手动建立这个文件，并根据自己安装的Python路径添加即可，其内容如下：
    ```
    # Configure specific Python version.---user for boost.python---2018.10.12---
    # using python : 3.6.1
    : D:/Anaconda3/Anaconda361/python.exe
    : D:/Anaconda3/Anaconda361/include #directory that contains pyconfig.h
    : D:/Anaconda3/Anaconda361/libs    #directory that contains python361.lib
    : <toolset>msvc ;
    ```
3. 如上配置完成后，在VS Developer Command Prompt命令行执行如下命令：
    ```
    b2 toolset=msvc-14.0 --with-python variant=debug runtime-debugging=on link=static --user-config=user-config.jam stage address-model=64 
    ```
    如果是32位系统，去掉address-model=64即可。

    如上三步完成后会生成一个stage文件夹和其它文件夹。这里只需要stage文件夹，此是我们想要的。在这个文件加下的lib文件夹下生成了**.lib文件，如libboost_numpy36-vc140-mt-gd-x64-1_68.lib等。

    如此便完成了Boost Library的安装。

## 下一步介绍Boost::Python的使用教程：

1. 打开VS建立一个工程，可以是Win32 Console Application， 或Win32 Project， 或Empty Project。然后右键单击所建的工程，找到最后一个选项：Properties --> C/C++ --> General --> Additional Include Directories，加入Boost头文件boost_1_68_0\boost；注意，如果直接加入路径..\boost_1_68_0\boost可能会出错，找不到头文件的错误，则应该这样添加：  
../boost_1_68_0\boost\..。注意这里../替换为你的Boost解压路径；然后配置生成的lib文件路径：Properties --> Linker --> General --> Additional Library Directories，加入boost_1_68_0\stage\lib路径；如上在配置头文件路径和库文件路径的时候，也需要如法添加Python的头文件和库文件。

2. Properties --> Linker --> Input --> Additional Dependencies加入boost_1_68_0\stage\lib文件夹下生成的库文件名lib**.lib。若直接加入lib**.lib，一般会出现找不到库文件的错误，所以可以把它的名字改为**.lib，即去掉开头的lib即可。

如上两步即完成VS与Boost::Python的配置工作，下一步看一下Boost::Python与C++接口的使用示例：

```
#include <boost/python.hpp>
#include<iostream>
#include<stdio.h>
using namespace boost::python;
//#define BOOST_PYTHON_STATIC_LIB
 
char const* greet()
{
	return "hello, world";
}
 
 
BOOST_PYTHON_MODULE(boostpy03)			// Python 模块开始
{
	using namespace boost::python;		// 打开命名空间
	def("greet", greet);
}
```

如上代码即是利用C++编写Python模块，一切基本上都是按照C++的语法编写即可。这块代码：

```
BOOST_PYTHON_MODULE(boostpy03)            // Python 模块开始
{
    using namespace boost::python;        // 打开命名空间
    def("greet", greet);
}
```

中BOOST_PYTHON_MODULE(boostpy03) 的boostpy3即为建立的工程名字，这里要保持一致。

为了要在Python下调用C++编写的模块，需要生成dll文件，而不是exe文件。需要在VS下进行如下配置：  
Properties --> Configuration Properties --> General --> Project Defaults --> Configuration Type改为Dynamic Library(.dll)即可，在Build Solution的时候会生成boostpy03.dll文件。

然后将boostpy03.dll更名为boostpy03.pyd文件并拷贝到Python路径下，如直接拷贝到Python的安装路径下，在该路径下有python.exe文件。我这里是通过Anaconda安装的Python3，在把boostpy03.pyd文件拷贝到Python的安装路径之下后，通过Anaconda Prompt打开Python，导入模块，运行结果如下：


PS:在编译Boost库时，如果采用默认则会编译为32位的库，利用address-model=64选项则会编译为64位的库。同时注意，VS标题栏中Debug --> 64方可与64位库正确配置。注意还需要将VS的cl.exe加入到环境变量中。