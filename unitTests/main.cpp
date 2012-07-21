#include <QtCore>
#include <QCoreApplication>
#include <QDebug>

#include "inc/asyncUnitTesting.h"
#include "inc/globals.h"

int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);
	serialConnection = new IPDS::SerialIO;
	QCoreApplication app(argc, argv);
	QStringList args = app.arguments();
	QString argument;
	/* list of valid arguments */
    QString portName("--port=");

	for (int i = 1; i < args.size(); ++i) {
		argument = args.at(i);
		if (argument.startsWith(portName)) {
			portName = argument.right(argument.length() - portName.length());
			qDebug() << "Port name:"<< portName;
		} else {
			qDebug() << "Uknown arg:" << args.at(i);
		}
	}
	if(portName.isEmpty()) {
		qDebug() << "Error: you must specify a serial port, eg. --port=/dev/ttyUSB0" << endl;
	}

	serialConnection->openPort(portName);
	serialConnection->setupPort(115200, 8, "none", 1); // SM
	if (serialConnection->isOpen() == true) {
		qDebug() << "port open, starting communication threads";
		serialConnection->communicate();
	} else {
		qDebug() << "error port not open";
	}
	smPingTest();
	return a.exec();
}

void smPingTest() {
	unsigned char rxData[10];
	unsigned char enableSM = 0x0d;
	unsigned int bytesRead;
	QElapsedTimer roundTrip;

	serialConnection->setupPort(115200, 8, "none", 1); // SM
	serialConnection->communicate();
	while (1) {
		roundTrip.start();
		serialConnection->writeData(&enableSM, 1);
		bytesRead = serialConnection->readData(&rxData[0], 3);
		if(bytesRead == 3) {
			qDebug() << "Sent one byte and recieved three bytes in" << roundTrip.elapsed() << "msec(s)";
		} else {
			qDebug() << "Read came up short, expected 3 but read " << bytesRead << "in " << roundTrip.elapsed()
					<< " msec(s)";
		}
	}
}

void FreeEMSPacketCounter() {
//	unsigned long numPackets = 0;
//	unsigned long numBadPackets = 0;
	QString mode = "FREEEMS";
	serialConnection->setupPort(115200, 8, "none", 1); // SM
	serialConnection->communicate();
	serialConnection->setDataMode(mode);

	while (1) {

	}

}
