TEMPLATE = app
TARGET = unitTests 
QT        += core 
HEADERS   += ../src/inc/CircularBuffer.h
SOURCES   += main.cpp \
			../src/CircularBuffer.cpp
FORMS	  +=
RESOURCES +=

QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

#default make spec stuff
INCLUDEPATH *= ../src/inc/public
INCLUDEPATH *= ../src/inc
INCLUDEPATH *= ../src

