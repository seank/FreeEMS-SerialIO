#include <QtCore>
#include <QCoreApplication>
#include "../inc/SerialIO.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	IPDS::SerialIO *serialConnection = new IPDS::SerialIO;
	serialConnection->openPort("/dev/ttyUSB0");
	serialConnection->setupPort(115200, 8, "odd", 1);
	if (serialConnection->isOpen() == true) {
		std::cout << "port open, starting communication threads ";
		serialConnection->communicate();
	} else {
		std::cout << "error port not open";
	}
    return a.exec();
}
