/*
 * SerialIO.h
 *
 *  Created on: Nov 15, 2011
 *      Author: seank
 */

#ifndef SERIALIO_H_
#define SERIALIO_H_

#include <SerialIO-types.h>
#include <qglobal.h>

#ifdef SERIALIO_LIB
# define SERIALIO_EXPORT Q_DECL_EXPORT
#else
# define SERIALIO_EXPORT Q_DECL_IMPORT
#endif

namespace IPDS {
class SerialIOPrivate;
class SERIALIO_EXPORT SerialIO: public QThread {
//	Q_OBJECT
public:
	SerialIO();
	virtual ~SerialIO();
	int setupPort(int baud, int databits, const QString& parity, int stop); //TODO change this to a struct will FULL parameters
	void flushRX();
	void setMode(QString& mode);
	void openPort(QString);
	bool isOpen();
	int readData(unsigned char* buf, unsigned int numBytes);
	void addByte(unsigned char& byte);
	void writeData(const void* data, unsigned int size);
	void setDataMode(QString&);
//	void writeData(QVector data);
	bool isCommunicating();
	void communicate();
	void closePort();
	void run();
	void writeString(QString&);
	QString getVersion();

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
	SerialIOPrivate * const d_ptr;
};

} /* namespace IPDS */
#else
#warning "SERIALIO_H_ already defined sort it out!"
#endif /* SERIALIO_H_ */
