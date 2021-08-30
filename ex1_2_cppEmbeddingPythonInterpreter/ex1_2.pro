TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += hello_world.cpp

PYTHON391 = "G:\bin\Python39"
win32:INCLUDEPATH += $$quote($$PYTHON391\include)
#win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0)

CONFIG(debug, debug|release) {
#debug
win32:LIBS += $$quote($$PYTHON391\libs\python39_d.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\libboost_python39-vc141-mt-gd-x64-1_75.lib)
}else{
#release
win32:LIBS += $$quote($$PYTHON391\libs\python39.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\libboost_python39-vc141-mt-x64-1_75.lib)
}
#unix:INCLUDEPATH += $$quote(/home/lichangsheng/desktop/boost/include)
#unix:INCLUDEPATH += $$quote(/home/lichangsheng/desktop/anaconda3/include/python3.7m)
#unix:LIBS += $$quote(/home/lichangsheng/desktop/boost/lib/libboost_python37.so)
#unix:LIBS += $$quote(/home/lichangsheng/desktop/anaconda3/lib/libpython3.7m.so)



win32:LIBS += $$quote($$PYTHON391\libs\python39.lib)
#这里写为python39_d.lib,将弹出以下错误
#LINK : fatal error LNK1104: 无法打开文件“python39.lib”
#可能因为编译boost.python debug版本时，使用的就是python39.lib

win32 {

    CONFIG(debug, debug|release) {
    OUTDIR=debug
    }else{
    OUTDIR=release
    }
    FILE3=$$PWD/script.py
    FILE4=$$OUT_PWD/$$OUTDIR/script.py

    #复制script.py到exe所在目录
    #让exe可以调用script.py
    FILE3 ~= s,/,\\,g
    FILE4 ~= s,/,\\,g
    QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE3) $$quote($$FILE4) $$escape_expand(\\n\\t)
}

