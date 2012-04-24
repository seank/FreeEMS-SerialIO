TEMPLATE = app
TARGET = asyncUnitTesting 

QT        += core 

HEADERS   +=
SOURCES   += main.cpp
FORMS	  +=
RESOURCES +=

# Straight Linux
linux-g++ {
	message("Straight Linux Build")
	unix:INCLUDEPATH += $$quote(/home/seank/work/workspaceCDT/asyncSerial/)
	unix:LIBS += $$quote(/home/seank/work/workspaceCDT/asyncSerial/libSerialIO.so)
}