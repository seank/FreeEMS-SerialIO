/*
 * CircularBuffer.h
 *
 *  Created on: Nov 22, 2011
 *      Author: seank
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include <QVector>
#include "inc/types.h"
//for debug
#include <QDebug>



namespace IPDS {
//TODO make STL complaint
class CircularBuffer {
public:
	CircularBuffer(unsigned int size);
	CircularBuffer();
	int getBytes(char& byteBase, int numBytes);
	bool pushByte(const unsigned char& byte);
	unsigned char getByte();
	unsigned int getTailIndex();
	unsigned int getHeadIndex();
	unsigned int bufferSize();
	void fillPayload(payloadVector&);
	void RXFromBuffer(unsigned char*, size_t size);
	void bufferBarf();
	void flush();
	void bufferInit();
	void bufferSaveLastAsFirst();
	virtual ~CircularBuffer();
private:
	unsigned int m_head;
	unsigned int m_tail;
	unsigned char *m_data;
	unsigned int m_bufferSize;
	bool m_bufFull;
//	QMutex busyInput;
//	QMutex busyOutput;
};

} /* namespace IPDS */
#else
//#warning "CIRCULARBUFFER_H_ already defined, sort it out!"
#endif /* CIRCULARBUFFER_H_ */
