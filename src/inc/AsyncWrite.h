/*
 * AsyncWrite.h
 *
 *  Created on: Nov 16, 2011
 *      Author: seank
 */

#ifndef ASYNCWRITE_H_
#define ASYNCWRITE_H_

#include <QObject>
#include <QThread>
#include <QVector>
#include <QMutex>
#include <QWaitCondition>
#include <CircularBuffer.h>

#ifdef __WIN32__
  #include <io.h>
  #include <windows.h>
  #else
  #include <termios.h> // POSIX terminal control definitions
#endif

#define TX_BUF_SIZE	0x2000 //8KB buffer TODO make global

namespace IPDS {

class AsyncWrite: public QThread {
	Q_OBJECT
public:
	AsyncWrite(int *FD, CircularBuffer *writeBuffer);
	virtual ~AsyncWrite();
	void run();
	void shutdownThread();
signals:
	void TXByte(unsigned char);
	void TXError(int);
private:
	bool m_shutdownWriterThread;
	int *_FD;
	CircularBuffer *m_writeBuffer;
};

} /* namespace IPDS */
#else
#warning "ASYNCWRITE_H_ already defined sort it out!"
#endif /* ASYNCWRITE_H_ */
