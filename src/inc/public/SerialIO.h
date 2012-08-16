/*
 * SerialIO.h
 *
 *  Created on: Nov 15, 2011
 *      Author: seank
 */

#ifndef SERIALIO_H_
#define SERIALIO_H_

#include "serialIO-types.h"

namespace IPDS {
class SerialIOPrivate;
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

private:
	SerialIOPrivate* d;
};

} /* namespace IPDS */
#else
#warning "SERIALIO_H_ already defined sort it out!"
#endif /* SERIALIO_H_ */
