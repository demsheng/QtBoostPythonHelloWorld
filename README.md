## BoostPythonHelloWorld
2021-01-29

- 作者：李长圣
- 邮箱：sheng0619@163.com
- 功能：演示在 `qtcreator` 中使用 `boost.python` 库，实现c++ 和 python混合编程。
- 支持 `window10`  系统

### 实例介绍
+ 第一组 入门
	- `ex1_1_cpp2lib`  扩展python，`qtcreator` 中将使用`boost.python`库的cpp编译成lib,在python中调用该lib 。
	- `ex1_2_cppEmbeddingPythonInterpreter` 将python作为cpp程序的脚本，实际未使用boost::python
	- `ex1_3_QtEmbeddingPythonInterpreter` 与ex2类似，将python作为Qt GUI程序的脚本，实际未使用boost::python
	- `ex1_4_embedding` 使用boost.python嵌入python解释器到c++应用
	- `ex1_5_execfile` debug模式 exec_file失败，不知道为什么
+ 第二组 编写单独的wrapper
	- `ex2_1_MultFilesWrapper` 为c++源码，单独封装一个wrapper供python调用
	- `ex2_2_WrapperVector` 传递c++的`std::vector<A>`类型到python
+ 第三组 让python处理`c++`中的对象数据，此时是传递了一个c++对象的指针给python，不需要生成pyd格式的库。传递`c++`中的对象实例给python，让python处理，之后`c++`可以使用该处理后的对象实例。
	- `ex3_1_cpp_object_to_python_single_file` 传递c++中的对象实例到python
	- `ex3_2_cpp_object_to_python_mult_file` 同ex6，区别是分离成多个文件
	- `ex3_3_cpp_object_to_python_execfile` 传递c++对象实例到python，作相应计算后，返回c++。debug模式 exec_file失败，不知道为什么

编译运行实例，使用 `qtcreator` 打开各实例文件夹下的 `*.pro` 运行。

### vs2017 win10 编译boost.python，qt5 (qtcreator) 中使用该库
**注意：**
1. 均编译为lib静态库
	- `boost_python39-vc141-mt-gd-x64-1_75.lib` Debug版本
	- `boost_python39-vc141-mt-x64-1_75.lib` Release版本
2. 编译后的libboost_python39-vc141-mt-gd-x64-1_75.lib，需要去掉lib前缀
	- 可以不改库名，需要在cpp中加入以下宏
		```
		#define BOOST_ALL_NO_LIB
		//告诉boost禁用自动链接。
		```
3. qtcreator中使用 boost.python 和 python3.lib 库时，Debug Relesse时要选择编译好的对应的版本


- 下载安装python，版本 `python-3.9.1-amd64.exe`
	https://www.python.org/downloads/release/python-391/ 选择 `Windows installer (64-bit)`
	- 可能需要添加环境变量到PATH

- 编译 boost.python
	1. 下载解压boost，版本 `boost_1_75_0.zip`  https://dl.bintray.com/boostorg/release/1.75.0/source/  
	2. 打开 `VS 2017的开发人员命令提示符`进入解压的目录，`F:\MyProgram\QtProject\libs\boost_1_75_0`，运行
		```
		bootstrap.bat 
		```
		生成 `b2.exe`  
		**注意** 这里必须使用 `VS 2017的开发人员命令提示符`，可能对应下面的`architecture=x86`
	3. 编译
		```
		b2 stage --toolset=msvc-14.1 architecture=x86 address-model=64 --with-python link=static runtime-link=shared threading=multi debug release 
		```

		完成后会生成一个`F:\MyProgram\QtProject\libs\boost_1_75_0\stage`文件夹和其它文件夹。这里只需要stage文件夹，此是我们想要的。在这个文件加下的lib文件夹下生成了**.lib文件。  
		**注意**：编译完 boost.python，生成的静态库名字可能是`libboost_python39-vc141-mt-gd-x64-1_75`，需要改成`boost_python39-vc141-mt-gd-x64-1_75`  
		**注意**：如果 `runtime-link=static`，生成静态库`libboost_python39-vc141-mt-sgd-x64-1_75`，无法生成hello.dll动态链接库

- qt5 (qtcreator) 中使用该库  
	- http://download.qt.io/archive/qt 下载安装Qt，本实例使用的版本 `Qt 5.12.9`
	- qtcreat中，使用boost.python时  
		- `inclue`为`F:\MyProgram\QtProject\libs\boost_1_75_0`,其中的boost即为头文件。  
		- `lib`在`F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib`  
	- **注意：** 为了让qtcreator中能找到对应的库，这里需要修改库名，去掉前缀 `lib` 。  
		- `libboost_python39-vc141-mt-gd-x64-1_75.lib` 改为 `boost_python39-vc141-mt-gd-x64-1_75.lib`
		- `libboost_python39-vc141-mt-x64-1_75.lib` 改为 `boost_python39-vc141-mt-x64-1_75.lib`  
		不然将会找不到相应的库，qtcreator提示错误
			```
			LINK : fatal error LNK1181: 无法打开输入文件“F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\boost_python39-vc141-mt-x64-1_75.lib”
			```
	- qtcreator中使用boost.python，编译错误原因
		- boost.python 和 python3.lib 的 Debug Relesse版本要对应，例如
			- boost_python39-vc141-mt-gd-x64-1_75.lib 为debug版本。
			- boost_python39-vc141-mt-x64-1_75.lib 为release版本。  
	
			Qtcreator中Debug模式编译程序时，*.pro中要使用debug版本库
			```
			win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost\vc141-x64\lib\boost_python39-vc141-mt-gd-x64-1_75.lib)
			```
			否则可能弹出以下错误，无法打开文件
			```
			LINK : fatal error LNK1104: 无法打开文件“F:\MyProgram\QtProject\libs\boost\vc141-x64\lib\boost_python39-vc141-mt-gd-x64-1_75.lib”
			```
- 库名解释 libboost_regex-vc71-mt-sgd-x86-1_34.lib 

	- `lib` On Windows, only ordinary static libraries use the lib prefix
	- `vc71` 使用的编译器
	- `mt` multithreading support enabled
	- sgd
		- s	runtime-link=static 有该值不能用来生成hello.dll动态链接库
		- g	using debug versions of the standard and runtime support libraries.	runtime-debugging=on
		- d variant=debug模式，qtcreator中debug模式选用有该标示的库


## 参考 [boost学习笔记（windows+vs2017+boost1.67 64位编译）](https://blog.csdn.net/maosijunzi/article/details/80750307?utm_medium=distribute.wap_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.wap_blog_relevant_pic&depth_1-utm_source=distribute.wap_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.wap_blog_relevant_pic)

环境：windows10+vs2017+boost1_67 64位

### boost下载
下载地址：https://dl.bintray.com/boostorg/release/1.67.0/binaries/
找到boost_1_67_0-msvc-14.1-64.exe并下载

### 安装
执行boost_1_67_0-msvc-14.1-64.exe，选择安装目录进行安装  
**注意** 安装目录`F:\MyProgram\QtProject\libs\boost\boost_1_75_0\lib64-msvc-14.1`下有编译好的所有库

### 编译
进入boost安装目录，执行bootstrap.bat，稍等几分钟，会生成bjam.exe文件。
然后打开vs2017 64位命令行，在开始菜单中的vs2017下。进入boost目录，执行下面命令：
```
bjam stage --toolset=msvc-14.1 architecture=x86 address-model=64 --without-graph --without-graph_parallel --stagedir="D:\local\boost_1_67_0\bin\vc141-x64" link=static runtime-link=shared runtime-link=static threading=multi debug release  
```
等待很长的时间之后。

### 配置vs
- 右键项目 》属性 》C/C++ 》Addtional Include Directories 》添加boost目录
- 右键项目 》属性 》Linker 》General 》Addtional Library Directories 》添加boost下编译好的lib目录
- 右键项目 》属性 》Linker 》Input 》Addtional Dependencies 》添加依赖的库名称