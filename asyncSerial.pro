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
PUBLIC_HEADERS += src/inc/public/SerialIO.h
HEADERS += src/inc/SerialIO_p.h \ 
	src/inc/AsyncRead.h \
    src/inc/AsyncWrite.h \
    src/inc/CircularBuffer.h \
    src/inc/byteDefinitions.h \
    src/inc/globals.h
SOURCES += src/AsyncRead.cpp \
    src/AsyncWrite.cpp \
    src/CircularBuffer.cpp \
    src/SerialIO.cpp \
    src/globals.cpp

# Cross compilation
win32-x-g++ { 
    message("Crosscompiling on Unix to Windows")
    INCLUDEPATH *= $$quote(/home/seank/work/workspaceCDT/asyncSerial/)
    QMAKE_CXXFLAGS -= -Werror
}

# /usr/local/i686-pc-mingw32/
# Straight Mac-OS (OS-X)
mac { 
    message("Mac OS-X Build")
    unix:INCLUDEPATH *= /opt/local/include
}

# Straight Linux
linux-g++:message("Straight Linux Build")
INCLUDEPATH *= src/

# unix:INCLUDEPATH += $$quote(/home/seank/work/workspaceCDT/asyncSerial/)
# Native Windows Build
win32 { 
    message("Straight compile on windows")
    CONFIG *= dll
    DEFINES += QT_NODLL
    win32:LIBS *= -Lc:/mingw/lib \
        -lwsock32
}
unix { 
    target.path = $$INSTALL_ROOT/usr/local/lib
    headers.files = src/inc/public/SerialIO.h
    headers.path = $$INSTALL_ROOT/usr/local/include
}
INSTALLS += target \
    headers
