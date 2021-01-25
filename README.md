## BoostPythonHelloWorld

- 作者：李长圣
- 邮箱：sheng0619@163.com
- 功能：演示在 `qtcreator` 中编译 `boost.python` 程序为静态库。
- 支持 `window10`  系统



### 编译运行
使用 `qtcreator` 打开 `BoostPythonHelloWorld.pro` 编译运行

### window10 安装 qt 和 boost.python

1. http://download.qt.io/archive/qt 下载安装Qt。   
本实例使用的版本 `Qt 5.12.9`
2. https://www.boost.org/ 下载 Boost  
本实例使用的版本为 `boost_1_75_0.zip` 

    - 打开VS Developer Command Prompt命令行，定位到Boost解压后的文件夹，在命令行执行 `booststrap.bat` ，将在文件夹下生  成 b2.exe及bjam.exe和project-config.jam等文件.

    - 其中project-config.jam文件不需要修改，保持默认即可，其内容如下：
        ```
        import option ;
        using msvc ;
        option.set keep-going : false ;
        ```
        而user-config.jam文件需要手动建立这个文件，并根据自己安装的Python路径添加即可，其内容如下：

        ```
        # Configure specific Python version.---user for boost.python---2018.10.12---
        # using python : 3.7.4
        : D:/WinPython_3_7_4/WPy64-3740/python-3.7.4.amd64/python.exe
        : D:/WinPython_3_7_4/WPy64-3740/python-3.7.4.amd64/include #directory that contains pyconfig.h
        : D:/WinPython_3_7_4/WPy64-3740/python-3.7.4.amd64/libs    #directory that contains python361.lib
        : <toolset>msvc ;
        ```
    - 如上配置完成后，在VS Developer Command Prompt命令行执行如下命令：
        ```
        b2 toolset=msvc-14.1 --with-python variant=debug runtime-debugging=on link=static --user-config=user-config.jam stage address-model=64 
        ```
        如上三步完成后会生成一个stage文件夹和其它文件夹。这里只需要stage文件夹，此是我们想要的。在这个文件加下的lib文件夹下生成了**.lib文件，如libboost_numpy36-vc140-mt-gd-x64-1_68.lib等。
3. 配置 `BoostPythonHelloWorld.pro`，见源码。
4. 打开 `qtcreator` 编译运行项目 `BoostPythonHelloWorld.pro` 。
5. 然后将helloworld.dll更名为helloworld.pyd. 通过D:\WinPython_3_7_4\WPy64-3740\WinPython Command Prompt.exe，进入helloworld.pyd文件夹，导入模块，运行结果如下：
    ```
    import helloworld
    print(helloworld.greet())
    ```
    输出
    ```
    hello, world
    ```
