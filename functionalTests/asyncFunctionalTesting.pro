TEMPLATE = app
TARGET = asyncFunctionalTesting
QT += core
HEADERS += inc/asyncFunctionalTesting.h \
    inc/asyncFunctionalTesting.h \
    inc/globals.h \
    inc/globals.h
SOURCES += smTestStats.cpp \
    smTestStats.cpp \
    main.cpp
FORMS += 
RESOURCES += 
VERSION = 0.1.0
CONFIG += console
# QMAKE_CXXFLAGS *= -Wall
# QMAKE_CXXFLAGS *= -Werror
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

INCLUDEPATH *= ../src/inc/public/
INCLUDEPATH *= inc/
PRE_TARGETDEPS += "../libSerialIO.so"
LIBS += -L$$quote(../) -lSerialIO

# Straight Linux
linux-g++ { 
    message("Straight Linux Build")
    unix:INCLUDEPATH += $$quote(../src/inc/public)
    CONFIG(debug, debug|release) {
    	PRE_TARGETDEPS += "../libSerialIO.so"
		LIBS += -L$$quote(../) -lSerialIO
    } else {
#		DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
		PRE_TARGETDEPS += "../libSerialIO.so"
    	LIBS += -L$$quote(../) -lSerialIO
    }
}

# Win32 MinGW
win32 { 
    CONFIG(debug, debug|release) {
    	PRE_TARGETDEPS += "../debug/SerialIO0.dll"
		LIBS += -L$$quote(../debug/) -lSerialIO0
    } else {
		DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
	P	RE_TARGETDEPS += "../release/SerialIO0.dll"
    	LIBS += -L$$quote(../release/) -lSerialIO0
    }
`   win32:LIBS *= -Lc:/mingw/lib \
        -lwsock32
}