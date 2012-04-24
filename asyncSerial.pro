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
SOURCES += unitTests/main.cpp \
    AsyncRead.cpp \
    AsyncWrite.cpp \
    CircularBuffer.cpp \
    SerialIO.cpp \
    globals.cpp
