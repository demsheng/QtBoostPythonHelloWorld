QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TEMPLATE = app #表示项目是应用程序模式

DESTDIR = ../bin #定义项目编译之后生成的结果文件的存放路径
CONFIG += c++11

PYTHON391 = "G:\bin\Python39"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#win32:INCLUDEPATH += ../pyInterpreter

#win32 { #表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错
#    LIBS += ../bin/python_interpreter.lib #包含项目需要用到的共享库
#}

#unix { #表示Linux环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错
#    LIBS += ../bin/python_interpreter.so #包含项目需要用到的共享库，注意文件名多了关键字"lib"，扩展名是.so
#}


SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    cspythonhello.h

FORMS += \
    mainwindow.ui

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

win32:INCLUDEPATH += $$quote($$PYTHON391\include)
#win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\include)
#win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0)

CONFIG(debug, debug|release) {
win32:LIBS += $$quote($$PYTHON391\libs\python39_d.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\libboost_python39-vc141-mt-gd-x64-1_75.lib)
}else{
win32:LIBS += $$quote($$PYTHON391\libs\python39.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\libboost_python39-vc141-mt-x64-1_75.lib)
}

#win32:LIBS += $$quote(F:\MyProgram\QtProject\boost_1_75_0\stage\lib\boost_python37-vc141-mt-gd-x64-1_75.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\boost_1_75_0\stage\lib\boost_numpy37-vc141-mt-gd-x64-1_75.lib)
#win32:LIBS += $$quote(D:\WinPython_3_7_4\WPy64-3740\python-3.7.4.amd64\libs\python37.lib)

#win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\boost\include\boost-1_75)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost\lib\boost_python37-vc141-mt-gd-x64-1_75.dll)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost\lib\boost_numpy37-vc141-mt-gd-x64-1_75.dll)



BOOST_1_75_0 = "G:\MyProgram\QtProject\libs\boost_1_75_0"
win32:INCLUDEPATH += $$quote($$BOOST_1_75_0)

CONFIG(debug, debug|release) {
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\libs\python39_d.lib)
win32:LIBS += $$quote($$BOOST_1_75_0\stage\lib\libboost_python39-vc141-mt-gd-x64-1_75.lib)
}else{
#win32:LIBS += $$quote($$BOOST_1_75_0\stage\lib\libboost_python39-vc141-mt-x64-1_75.lib)
#这里是动态库，如果要使用
#需要将下面两个文件复制到exe目录！！！
#boost_python39-vc141-mt-x64-1_75.dll
#boost_python39-vc141-mt-x64-1_75.lib
#win32:LIBS += $$quote($$BOOST_1_75_0\stage\lib\boost_python39-vc141-mt-x64-1_75.lib)
#使用静态库！！！
win32:LIBS += $$quote($$BOOST_1_75_0\stage\lib\libboost_python39-vc141-mt-x64-1_75.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\boost_python39-vc141-mt-x64-1_75.lib)
}

#win32 {

#    OUTDIR=bin

#    FILE3=$$PWD/../script.py
#    FILE4=$$OUT_PWD/../$$OUTDIR/script.py

#    #复制script.py到exe所在目录
#    #让exe可以调用script.py
#    FILE3 ~= s,/,\\,g
#    FILE4 ~= s,/,\\,g
#    QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE3) $$quote($$FILE4) $$escape_expand(\\n\\t)
#}
