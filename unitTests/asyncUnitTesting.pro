TEMPLATE = app
PRE_TARGETDEPS += "../libSerialIO.so"
TARGET = asyncUnitTesting
QT += core
HEADERS += inc/asyncUnitTesting.h \
    inc/asyncUnitTesting.h \
    inc/globals.h \
    inc/globals.h
SOURCES += main.cpp
FORMS += 
RESOURCES += 
VERSION = 0.0.1
#QMAKE_CXXFLAGS *= -Wall
#QMAKE_CXXFLAGS *= -Werror
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

# Straight Linux
linux-g++ { 
    message("Straight Linux Build")
    unix:INCLUDEPATH += $$quote(/home/seank/work/workspaceCDT/asyncSerial/)
    unix:LIBS += $$quote(/home/seank/work/workspaceCDT/asyncSerial/libSerialIO.so)
}
