#include <iostream>

#include <QtCore>
#include <QCoreApplication>
#include <QDebug>

#include "inc/asyncFunctionalTesting.h"
#include "inc/globals.h"
#include "smTestStats.cpp"

using namespace std;

smTestStats smTestStats;

int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);
	serialConnection = new IPDS::SerialIO;
	QCoreApplication app(argc, argv);
	QStringList args = app.arguments();
	QString argument;
	/* list of valid arguments */
    QString portName("--port=");

    smTestStats.numChecks = 500000;

	for (int i = 1; i < args.size(); ++i) {
		argument = args.at(i);
		if (argument.startsWith(portName)) {
			portName = argument.right(argument.length() - portName.length());
			qDebug() << "Port name:"<< portName;
		} else {
			qDebug() << "Uknown arg:" << args.at(i);
		}
	}
	if(portName == "--port=") {
		qDebug() << "Error: you must specify a serial port, eg. --port=/dev/ttyUSB0" << endl;
		return -1;
	}
	qDebug() << portName;
	serialConnection->openPort(portName);
	serialConnection->setupPort(115200, 8, "none", 1); // SM
	if (serialConnection->isOpen() == true) {
		qDebug() << "port open, starting communication threads";
		serialConnection->communicate();
	} else {
		qDebug() << "error port not open";
	}
	smPingTest();
	//FreeEMSPacketCounter();
	printSMResults();
	return a.exec();
}

void smPingTest() {
	cout << "Executing SM Ping Test" << endl;
	unsigned char rxData[10];
	unsigned char enableSM = 0x0d;
	unsigned int bytesRead;
	unsigned int numRuns = smTestStats.numChecks;
	QElapsedTimer roundTrip;
	QString mode = "RAW";
	serialConnection->setDataMode(mode);
	serialConnection->setupPort(115200, 8, "none", 1); // SM
	serialConnection->communicate();
	while (numRuns) {
		roundTrip.start();
		serialConnection->writeData(&enableSM, 1);
		bytesRead = serialConnection->readData(&rxData[0], 3);
		if(bytesRead == 3) {
			qDebug() << "Sent one byte and received three bytes in " << roundTrip.elapsed() << " msec(s)";
			if (((rxData[0] == 0xE1) || (rxData[0] == 0xE0)) && (rxData[2] == 0x3E)) {
				smTestStats.acksRX++;
				if (rxData[1] == 8)
					smTestStats.numResets++;
			} else {
				smTestStats.acksCorrupt++;
			qDebug() << " read " << rxData[0] << rxData[1] << rxData[2] << endl;
			}
		} else {
			qDebug() << "Read came up short, expected 3 but read " << bytesRead << " in " << roundTrip.elapsed()
					<< " msec(s)";
			smTestStats.acksMissed++;
			/* flush rx buffer so the next iteration has a fresh start */
			serialConnection->flushRX();
		}
		--numRuns;
	}
}

void FreeEMSPacketCounter() {
//	unsigned long numPackets = 0;
//	unsigned long numBadPackets = 0;
	QString mode = "FREEEMS";
	serialConnection->setDataMode(mode);
	serialConnection->setupPort(115200, 8, "odd", 1); // SM
	serialConnection->communicate();

	while (1) {

	}
}

void printSMResults() {

	cout << "---------- Dumping SM Test Results ----------" << endl;
	cout << endl;
	cout << "Pinged the Serial Monitor " << smTestStats.numChecks << " Times" << endl;
	cout << "Detected " << smTestStats.numResets << " SM resets" << endl;
	cout << "Received " << smTestStats.acksRX << " good ACKs" << endl;
	cout << "Missed " << smTestStats.acksMissed << " ACKs" << endl;
	cout << "Received " << smTestStats.acksCorrupt << " corrupted ACKs" << endl;
	cout << endl;
	cout << "Success Rate = " << (double)smTestStats.acksRX / smTestStats.numChecks << endl;

}
