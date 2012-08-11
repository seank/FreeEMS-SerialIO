#!/bin/bash

sudo cp libSerialIO.so.0.0.1 /usr/local/lib/
sudo cp src/inc/public/SerialIO.h /usr/local/include/SerialIO.h
sudo ldconfig

if [ -f SerialIO0.dll ] then
	sudo cp release/*.dll /usr/local/win32/lib/
fi
