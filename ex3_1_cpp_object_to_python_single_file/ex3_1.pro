TEMPLATE = app
TARGET = main
#CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt
#CONFIG += staticlib #生成hello.lib静态链接库
#CONFIG += dll #生成hello.dll动态链接库
#DESTDIR = ../bin #定义项目编译之后生成的结果文件的存放路径

SOURCES += \
    main.cpp \

PYTHON391 = "G:\bin\Python39"
BOOST_1_75_0 = "G:\MyProgram\QtProject\libs\boost_1_75_0"

win32:INCLUDEPATH += $$quote($$PYTHON391\include)
win32:INCLUDEPATH += $$quote($$BOOST_1_75_0)
win32:LIBS += $$quote($$PYTHON391\libs\python39.lib)

CONFIG(debug, debug|release) {
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\libs\python39_d.lib)
win32:LIBS += $$quote($$BOOST_1_75_0\stage\lib\libboost_python39-vc141-mt-gd-x64-1_75.lib)
}else{
win32:LIBS += $$quote($$BOOST_1_75_0\stage\lib\libboost_python39-vc141-mt-x64-1_75.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\boost_python39-vc141-mt-x64-1_75.lib)
}




