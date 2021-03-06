/*
 * AsyncRead.h
 *
 *  Created on: Nov 15, 2011
 *      Author: seank
 */

#ifndef ASYNCREAD_H_
#define ASYNCREAD_H_

#include <QThread>
#include <QObject>
#include <iostream>
#include <CircularBuffer.h>
#include <byteDefinitions.h>
#include <globals.h>
#include <SerialIO-types.h>
#include <QDebug>
#include <QString>
#include <QWaitCondition>

#ifdef __WIN32__
  #include <io.h>
  #include <windows.h>
#else
  #include <termios.h> // POSIX terminal control definitions
  #include <unistd.h>
#endif

namespace IPDS {

class AsyncRead: public QThread {
	Q_OBJECT
public:
	AsyncRead(int *FD, CircularBuffer *buffer);
	virtual ~AsyncRead();
	void run();
	void setExpectedBytes(unsigned int numBytes);
	void setMode(QString& mode);
	QString getMode();
	void shutdownThread();
	void flush();
signals:
	void RXBlock(payloadVector);
	void RXPacket(payloadVector);
	void RXError(int);
private:
	bool m_shutdownReaderThread;
	bool m_requestFlush;
	bool m_nextIsEscaped;
	bool m_insidePacket;
	unsigned char m_lastByte;
	unsigned int m_bytesExpected;
	/* counters TODO class these counters*/
	unsigned long int m_numConsecutiveGarbageBytes;
	unsigned long int m_numPacketsRX;
	unsigned long int m_numGarbageBytes;
	unsigned long int m_numTotalRXBytes;
	int *m_FD;
	QString m_mode;
	IPDS::CircularBuffer *m_readBuffer;
	void processByte(unsigned char& byte);
};

} /* namespace IPDS */
#else
#warning "Header ASYNCREAD_H_ already defined sort it out!"
#endif /* ASYNCREAD_H_ */
