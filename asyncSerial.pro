TEMPLATE = lib
TARGET = asyncSerial
VERSION = 0.0.1
TARGET = SerialIO
QMAKE_CXXFLAGS *= -Wall
QMAKE_CXXFLAGS *= -Werror
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
CONFIG *= qt \
    warn_on \
    thread \
    release \
    debug
QT += core
QT -= gui
HEADERS += inc/AsyncRead.h \
    inc/AsyncWrite.h \
    inc/CircularBuffer.h \
    inc/SerialIO.h \
    inc/byteDefinitions.h \
    inc/globals.h \
    inc/types.h
SOURCES += AsyncRead.cpp \
    AsyncWrite.cpp \
    CircularBuffer.cpp \
    SerialIO.cpp \
    globals.cpp

# Cross compilation
win32-x-g++ { 
    message("Crosscompiling on Unix to Windows")
    INCLUDEPATH *= $$quote(/home/seank/work/workspaceCDT/asyncSerial/)
    QMAKE_CXXFLAGS -= -Werror
#   /usr/local/i686-pc-mingw32/
}
# Straight Mac-OS (OS-X)
mac { 
    message("Mac OS-X Build")
    unix:INCLUDEPATH *= /opt/local/include
}
# Straight Linux
linux-g++ {
	message("Straight Linux Build")
#	unix:INCLUDEPATH += $$quote(/home/seank/work/workspaceCDT/asyncSerial/)
}
# Native Windows Build
win32 { 
    message("Straight compile on windows")
    INCLUDEPATH *= $$quote(/home/seank/work/workspaceCDT/asyncSerial/)
#    INCLUDEPATH *= $$quote(/usr/include/i386-linux-gnu/)
#    INCLUDEPATH *= $$quote(/usr/include/)
	INCLUDEPATH *= $$quote(/home/seank/work/workspaceCDT/mxe/usr/i686-pc-mingw32/include/)
    
    win32:LIBS *= -Lc:/mingw/lib \
        -lwsock32
}
    