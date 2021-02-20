### qtcreator 打开 QtBoostPythonInterpreterHelloWorld.pro 运行

### vs2017 qt5 win10 编译boost.python，并使用

- 下载安装python，版本 `python-3.9.1-amd64.exe`
	https://www.python.org/downloads/release/python-391/ 选择 `Windows installer (64-bit)`
	- 可能需要添加环境变量到PATH

- 下载解压boost，版本 `boost_1_75_0.zip`  https://dl.bintray.com/boostorg/release/1.75.0/source/  
	1. 打开 `VS 2017的开发人员命令提示符`进入解压的目录，`F:\MyProgram\QtProject\libs\boost_1_75_0`，运行
		```
		bootstrap.bat 
		```
		生成 `b2.exe`
	2. 编译
		```
		b2 stage --toolset=msvc-14.1 architecture=x86 address-model=64 --with-python link=static runtime-link=shared runtime-link=static threading=multi debug release 
		```
		使用boost.python时  
		`inclue`为`F:\MyProgram\QtProject\libs\boost_1_75_0`,其中的boost即为头文件。  
		`lib`在`F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib`  
		**注意：**  
		为了让qtcreator中能找到对应的库，这里需要修改库名，去掉前缀 `lib` 。  
		`libboost_python39-vc141-mt-gd-x64-1_75.lib` 改为 `boost_python39-vc141-mt-gd-x64-1_75.lib`
		`libboost_python39-vc141-mt-x64-1_75.lib` 改为 `boost_python39-vc141-mt-x64-1_75.lib`
		不然将会找不到相应的库，qtcreator提示错误
		```
		LINK : fatal error LNK1181: 无法打开输入文件“F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\boost_python39-vc141-mt-x64-1_75.lib”
		```
	3. 使用，QtBoostPythonInterpreterHelloWorld.pro 配置
		```
		TEMPLATE = app
		CONFIG += console c++11
		CONFIG -= app_bundle
		CONFIG -= qt

		SOURCES += hello_world.cpp

		win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\include)
		win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0)

		#debug
		win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\libs\python39_d.lib)
		win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\boost_python39-vc141-mt-gd-x64-1_75.lib)
		#release
		win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\libs\python39.lib)
		win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\boost_python39-vc141-mt-x64-1_75.lib)

		#unix:INCLUDEPATH += $$quote(/home/lichangsheng/desktop/boost/include)
		#unix:INCLUDEPATH += $$quote(/home/lichangsheng/desktop/anaconda3/include/python3.7m)
		#unix:LIBS += $$quote(/home/lichangsheng/desktop/boost/lib/libboost_python37.so)
		#unix:LIBS += $$quote(/home/lichangsheng/desktop/anaconda3/lib/libpython3.7m.so)						
		```

### boost.python qtcreator编译错误原因

- boost.python 和 python3.lib 的 Debug Relesse版本要对应
	如 boost_python39-vc141-mt-gd-x64-1_75.lib 为debug版本
	Debug模式编译程序时，qtcreat.pro中要
	```
	win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost\vc141-x64\lib\boost_python39-vc141-mt-gd-x64-1_75.lib)
	```
	否则可能弹出以下错误，无法打开文件
	```
	LINK : fatal error LNK1104: 无法打开文件“F:\MyProgram\QtProject\libs\boost\vc141-x64\lib\boost_python39-vc141-mt-gd-x64-1_75.lib”
	```
	编译完 boost.python，生成的静态库名字可能是
	```
	libboost_python39-vc141-mt-gd-x64-1_75
	```
	需要改成
	```
	boost_python39-vc141-mt-gd-x64-1_75
	```
