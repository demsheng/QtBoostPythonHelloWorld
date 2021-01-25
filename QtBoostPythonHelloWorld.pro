#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T12:03:12
#
#-------------------------------------------------
#cmake -G "Visual Studio 15 2017 Win64" ..
# Desktop_Qt_5_12_9_MSVC2017_64bit-Release

QT += core gui

QT += widgets

TARGET = helloworld
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    main.cpp

win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\boost_1_75_0)
win32:INCLUDEPATH += $$quote(D:\WinPython_3_7_4\WPy64-3740\python-3.7.4.amd64\include)

win32:LIBS += $$quote(F:\MyProgram\QtProject\boost_1_75_0\stage\lib\boost_python37-vc141-mt-gd-x64-1_75.lib)
win32:LIBS += $$quote(F:\MyProgram\QtProject\boost_1_75_0\stage\lib\boost_numpy37-vc141-mt-gd-x64-1_75.lib)
win32:LIBS += $$quote(D:\WinPython_3_7_4\WPy64-3740\python-3.7.4.amd64\libs\python37.lib)

