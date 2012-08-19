TEMPLATE = app
TARGET = asyncUnitTesting
QT += core
HEADERS += inc/asyncUnitTesting.h \
    inc/asyncUnitTesting.h \
    inc/globals.h \
    inc/globals.h
SOURCES += smTestStats.cpp \
    smTestStats.cpp \
    main.cpp
FORMS += 
RESOURCES += 
VERSION = 0.0.1

# QMAKE_CXXFLAGS *= -Wall
# QMAKE_CXXFLAGS *= -Werror
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

# Straight Linux
linux-g++ { 
    message("Straight Linux Build")
    PRE_TARGETDEPS += "../libSerialIO.so"
    unix:INCLUDEPATH += $$quote(../src/inc/public)
    unix:LIBS += $$quote(../libSerialIO.so)
}
