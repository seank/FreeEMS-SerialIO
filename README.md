Welcome to FreeEMS-SerialIO!
########################## FreeEMS Serial IO QT Library ######################################

# About
This lib was intended to help make writing code that communicates with FreeEMS easy and consistent.

# How to Build

##########################  LINUX USERS #################################
To build and install this library please run the following commands:

1. <apt-get update && apt-get install  qt4-qmake libqt4-dev>

2. Run <qmake && make> from the root of this project.  If you want extended debug messages run <qmake "CONFIG += debug">.

3. If you were able to compile without issue run <sudo make install && sudo ldconfig>.  This will allow dependant applications to find this lib and the public headers.

# Windows
todo

# How to Use
todo

# TODO
Consider porting to other c/c++ frameworks/compilers.

# Links
Fred drew a rough guide to application structure and communication flow, it's
available at the following link: http://stuff.fredcooke.com/InterractingWithFreeEMS.png


