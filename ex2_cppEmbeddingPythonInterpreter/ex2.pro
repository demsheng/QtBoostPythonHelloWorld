TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += hello_world.cpp

win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\include)
win32:INCLUDEPATH += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0)

#debug
win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\libs\python39_d.lib)
win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\libboost_python39-vc141-mt-gd-x64-1_75.lib)
#release
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\python3_9_1\libs\python39.lib)
#win32:LIBS += $$quote(F:\MyProgram\QtProject\libs\boost_1_75_0\stage\lib\libboost_python39-vc141-mt-x64-1_75.lib)

#unix:INCLUDEPATH += $$quote(/home/lichangsheng/desktop/boost/include)
#unix:INCLUDEPATH += $$quote(/home/lichangsheng/desktop/anaconda3/include/python3.7m)
#unix:LIBS += $$quote(/home/lichangsheng/desktop/boost/lib/libboost_python37.so)
#unix:LIBS += $$quote(/home/lichangsheng/desktop/anaconda3/lib/libpython3.7m.so)


