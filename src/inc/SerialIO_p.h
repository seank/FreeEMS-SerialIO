/*
 * SerialIO.h
 *
 *  Created on: Nov 15, 2011
 *      Author: seank
 */

#ifndef SERIALIOP_H_
#define SERIALIOP_H_

/* System Includes */
#include <fcntl.h>

/* Local Includes */
#include <AsyncRead.h>
#include <AsyncWrite.h>
#include <SerialIO.h>

/* Conditional Includes */
#ifdef __WIN32__
  #include <io.h>
  #include <windows.h>

  typedef enum
  {
	NONE,
	ODD,
	EVEN
  }Parity;

#else
  #include <termios.h> // POSIX terminal control definitions
  #include <sys/ioctl.h>
  #include <sys/select.h>
#endif

#define TX_BUF_SIZE		0x2000 //8KB buffer TODO make global

typedef unsigned int speet_t;

namespace IPDS {

class SerialIOPrivate: public QThread {
	Q_OBJECT
public:
	SerialIOPrivate();
	virtual ~SerialIOPrivate();
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

#ifdef __WIN32__
	int win32_cfg_serial(unsigned int fd, int baud, int bits, QString parity, int stop);
#else
	struct termios m_oldtio;
	struct termios m_newtio;
#endif

	bool m_isOpen;
	bool m_isConfigured;
	bool m_isCommunicating;
	bool m_isStreaming;
	int m_FD;
	int m_numBytesExpected;
	int m_numBytesProcessed;
	unsigned int m_readBlockMS; //number of ms to block while waiting for a byte
	QString m_portName;
	unsigned char TXBuffer[TX_BUF_SIZE];
	unsigned int TXBytesLeft;
	QMutex m_readMutex;
	QString m_dataMode;
	IPDS::CircularBuffer *m_readBuffer;
	IPDS::CircularBuffer *m_writeBuffer;
	IPDS::AsyncRead *asyncReader;
	IPDS::AsyncWrite *asyncWriter;
};

} /* namespace IPDS */
#else
#warning "SERIALIOP_H_ already defined sort it out!"
#endif /* SERIALIOP_H_ */
