#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T12:03:12
#
#-------------------------------------------------
#cmake -G "Visual Studio 15 2017 Win64" ..
# Desktop_Qt_5_12_9_MSVC2017_64bit-Release

QT -= core gui

QT -= widgets

TARGET = python_interpreter
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../bin #定义项目编译之后生成的结果文件的存放路径

PYTHON391 = "G:\bin\Python39"

SOURCES += \
    python_interpreter.cpp

HEADERS += \
    python_interpreter.h

win32:INCLUDEPATH += $$quote($$PYTHON391\include)
#win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0)

CONFIG(debug, debug|release) {
win32:LIBS += $$quote($$PYTHON391\libs\python39_d.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\libboost_python39-vc141-mt-gd-x64-1_75.lib)
}else{
win32:LIBS += $$quote($$PYTHON391\libs\python39.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\boost_python39-vc141-mt-x64-1_75.lib)
}

