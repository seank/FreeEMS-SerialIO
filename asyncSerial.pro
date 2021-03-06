TEMPLATE = lib
VERSION = 0.1.0
TARGET = SerialIO
QMAKE_CXXFLAGS *= -Wall
QMAKE_CXXFLAGS *= -Werror
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
#Build directories
Release:DESTDIR = build/release
Release:OBJECTS_DIR = build/release
Release:MOC_DIR = build/release
Release:RCC_DIR = build/release
Release:UI_DIR = build/release
Debug:DESTDIR = build/debug
Debug:OBJECTS_DIR = build/debug
Debug:MOC_DIR = build/debug
Debug:RCC_DIR = build/debug
Debug:UI_DIR = build/debug
CONFIG *= qt \
    warn_on \
    thread \
    release
QT += core
QT -= gui
PUBLIC_HEADERS += src/inc/public/SerialIO.h \
    src/inc/public/SerialIO-types.h
HEADERS += src/inc/externalData.h \
    src/inc/SerialIO_p.h \
    src/inc/AsyncRead.h \
    src/inc/AsyncWrite.h \
    src/inc/CircularBuffer.h \
    src/inc/byteDefinitions.h \
    src/inc/globals.h
SOURCES += src/externalData.cpp \
    src/AsyncRead.cpp \
    src/AsyncWrite.cpp \
    src/CircularBuffer.cpp \
    src/SerialIO.cpp \
    src/globals.cpp
DEFINES += SERIALIO_LIB
DEFINES += LIB_VERSION="0.1.0"

# Default include paths
INCLUDEPATH *= src/
INCLUDEPATH *= src/inc
INCLUDEPATH *= src/inc/public/

# Default install paths
unix { 
    isEmpty(PREFIX):PREFIX = /usr/local
    message("ATTENTION, running 'make install' will install files under '" $$PREFIX "'. If you wish to change this, rerun qmake as follows 'qmake PREFIX=/desiredPath' instead.")
    target.path = $$PREFIX/lib
    headers.files = $$PUBLIC_HEADERS
    headers.path = $$PREFIX/include
    INSTALLS += target \
        headers
}

CONFIG(debug, debug|release):message("Building Debug Version, expect spew!")
    else { 
        DEFINES += QT_NO_WARNING_OUTPUT \
            QT_NO_DEBUG_OUTPUT
        message("Building Release Version, if you need debug symbols and debug messages rerun qmake like this 'qmake CONFIG+=debug'")
    }

# Cross compilation
win32-x-g++|win64-x-g++ { 
    message("Crosscompiling on Unix to Windows")
    CONFIG *= dll
    DEFINES += QT_NODLL
    LIBS *= -lwsock32
    isEmpty(PREFIX) { 
        PREFIX = /usr/local
        message("PREFIX not set, using /usr/local")
    }
    target.path = $$PREFIX/lib
    headers.files = $$PUBLIC_HEADERS
    headers.path = $$PREFIX/include
    INSTALLS += target \
        headers
}

# Straight Mac-OS (OS-X)
mac { 
    message("Mac OS-X Build")
    unix:INCLUDEPATH *= /opt/local/include
}

# Native Windows Build/MXE
win32-g++|win32-msvc { 
    message("Straight compile on windows")
    CONFIG += console # iirc we needed to to view debug output.....
    target.path = $$PREFIX/win32/lib
    headers.files = $$PUBLIC_HEADERS
    headers.path = $$PREFIX/win32/include
    INSTALLS += target \
        headers
    # win32:LIBS *= -Lc:/mingw/lib \
    LIBS *= -lwsock32
}

# QMAKE_LFLAGS += -enable-auto-import
# Straight Linux
linux-g++:message("Straight Linux Build")
