/*
 * SerialIO.h
 *
 *  Created on: Nov 15, 2011
 *      Author: seank
 */

#ifndef SERIALIO_H_
#define SERIALIO_H_

//#include <stdio.h> //for printf
//#include <fcntl.h>
//#include <string.h> // for memset
//#include <string>
//#include <inc/AsyncRead.h>
//#include <inc/AsyncWrite.h>
#include </home/seank/work/workspaceCDT/asyncSerial/src/inc/public/serialIO-types.h>

//#include <CircularBuffer.h>

//#include <QObject>
//#include <QString>
//#include <QWaitCondition>
//#include <QVector>
//#include <QMetaType>
//#include <QMutex>

//#include <errno.h>
//#include <unistd.h>
//#include <ctype.h>
//#include <sys/time.h>
//#include <sys/types.h>
//#include <fcntl.h>

//#ifdef __WIN32__
//  #include <io.h>
//  #include <windows.h>
//
//  typedef enum
//  {
//	NONE,
//	ODD,
//	EVEN
//  }Parity;
//
//#else
//  #include <termios.h> // POSIX terminal control definitions
//  #include <sys/ioctl.h>
//  #include <sys/select.h>
//#endif
//
//#define TX_BUF_SIZE 	0x2000 //8KB buffer TODO make global
//
//typedef unsigned int speet_t;

namespace IPDS {

class SerialIO: public QThread {
//	Q_OBJECT
public:
	SerialIO();
	virtual ~SerialIO();
	int setupPort(int baud, int databits, const QString& parity, int stop); //TODO change this to a struct will FULL parameters
	void flushRX();
	void setMode(QString& mode);
	void openPort(QString);
	bool isOpen();
	int readData(unsigned char* buf, size_t numBytes);
	void addByte(unsigned char& byte);
	void writeData(const void* data, size_t size);
	void setDataMode(QString&);
//	void writeData(QVector data);
	bool isCommunicating();
	void communicate();
	void closePort();
	void run();
	void writeString(QString&);

signals:
	void readBytesFinished(payloadVector);
	void readPacketFinished(payloadVector);
	void requestReadShutdown();
	void requestWriteShutdown();
	void haltReader();

public slots:
	void processRXError(int);
	void receivedRXBlock(payloadVector);
	void receivedRXPacket(payloadVector);
	void processTXError(int);

};

} /* namespace IPDS */
#else
#warning "SERIALIO_H_ already defined sort it out!"
#endif /* SERIALIO_H_ */
