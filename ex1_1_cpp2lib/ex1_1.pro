#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T12:03:12
#
#-------------------------------------------------
#cmake -G "Visual Studio 15 2017 Win64" ..
# Desktop_Qt_5_12_9_MSVC2017_64bit-Release

#为了让python能调用，必须编译成hello.dll动态链接库
#将hello.dll改成hello.pyd，才能在python中import

QT -= core gui
QT -= widgets

TARGET = hello
TEMPLATE = lib

#编译为静态库hello.lib
#CONFIG += staticlib

SOURCES += hello.cpp

DISTFILES += \
    test.py

win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\include)
win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0)

win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\libs\python39.lib)
#这里写为python39_d.lib,将弹出以下错误
#LINK : fatal error LNK1104: 无法打开文件“python39.lib”
#可能因为编译boost.python debug版本时，使用的就是python39.lib

CONFIG(debug, debug|release) {
#1. 使用boost静态库，生成的hello.dll可以直接改为hello.pyd，从python中导入使用
win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\libboost_python39-vc141-mt-gd-x64-1_75.lib)
#2. 使用boost动态库，生成的hello.dll改为hello.pyd，不能从python中直接导入使用
#需要复制boost_python39-vc141-mt-gd-x64-1_75.dll到hello.pyd同一目录，才可以从python中导入hello
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\boost_python39-vc141-mt-gd-x64-1_75.lib)
OUTDIR=debug

}else{

#1. boost静态库-成功
win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\libboost_python39-vc141-mt-x64-1_75.lib)
#2. boost动态库-成功
#需要复制boost_python39-vc141-mt-x64-1_75.dll到hello.pyd同一目录
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\boost_python39-vc141-mt-x64-1_75.lib)
OUTDIR=release
}

win32 {
    FILE1=$$OUT_PWD/$$OUTDIR/hello.dll
    FILE2=$$OUT_PWD/$$OUTDIR/hello.pyd

    FILE3=$$PWD/test.py
    FILE4=$$OUT_PWD/$$OUTDIR/test.py

    #复制gld.dll到gld.pyd
    #让test.py可以调用gld.pyd
    FILE1 ~= s,/,\\,g
    FILE2 ~= s,/,\\,g
    QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE1) $$quote($$FILE2) $$escape_expand(\\n\\t)

    #复制gld.dll到gld.pyd
    #让test.py可以调用gld.pyd
    FILE3 ~= s,/,\\,g
    FILE4 ~= s,/,\\,g
    QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE3) $$quote($$FILE4) $$escape_expand(\\n\\t)
}
