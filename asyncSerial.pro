TEMPLATE = lib
VERSION = 0.1.0
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

CONFIG(debug, debug|release) {
	message("Building Debug Version, expect spew!")
} else {
	DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
	message("Building Release Version")
}

PUBLIC_HEADERS += src/inc/public/SerialIO.h src/inc/public/SerialIO-types.h

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
    CONFIG *= dll
    DEFINES += QT_NODLL
    INCLUDEPATH *= src/
    target.path = $$INSTALL_ROOT/usr/local/win32/lib
    headers.files = $$PUBLIC_HEADERS
    headers.path = $$INSTALL_ROOT/usr/local/win32/include
    INSTALLS += target headers
}

# Straight Mac-OS (OS-X)
mac { 
    message("Mac OS-X Build")
    unix:INCLUDEPATH *= /opt/local/include
}

# Native Windows Build
win32 { 
    message("Straight compile on windows")
    CONFIG *= dll
    CONFIG += console
    DEFINES += QT_NODLL
    INCLUDEPATH *= src/
    target.path = $$INSTALL_ROOT/usr/local/win32/lib
    headers.files = $$PUBLIC_HEADERS
    headers.path = $$INSTALL_ROOT/usr/local/win32/include
    INSTALLS += target headers
#    win32:LIBS *= -Lc:/mingw/lib \
    LIBS *= -lwsock32
    QMAKE_LFLAGS += -enable-auto-import
}

# Straight Linux
linux-g++ { 
message("Straight Linux Build")
    INCLUDEPATH *= src/
    target.path = $$INSTALL_ROOT/usr/local/lib
    headers.files = $$PUBLIC_HEADERS
    headers.path = $$INSTALL_ROOT/usr/local/include
    INSTALLS += target headers
}
