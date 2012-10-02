/*
 * CircularBuffer.cpp
 *
 *  Created on: Nov 22, 2011
 *      Author: seank
 */

#include <CircularBuffer.h>

namespace IPDS {

CircularBuffer::CircularBuffer(unsigned int size) {
	m_data = new unsigned char[size];
	m_head = 0;
	m_tail = 0;
	m_bufferSize = size;
	m_bufFull = false;
	bufferInit();
//	busyInput.unlock();
//	busyOutput.unlock();
}

CircularBuffer::~CircularBuffer() {
	qDebug() << "~CircularBuffer() called";
//	delete[] m_data;
}

bool CircularBuffer::pushByte(const unsigned char& byte) {
	if (m_bufFull == true) {
		qDebug() << "buffer overrun";
		return false;
	} else {
		*(m_data + m_head) = byte;
		++m_head;
		if (m_head > m_bufferSize) {
			m_head = 0;
		}
		if (m_tail == m_head) {
			m_bufFull = true;
			qDebug() << "buffer full";
			return false;
		}
//		qDebug("added byte to buffer");
		return true;
	}
}

unsigned int CircularBuffer::bufferSize() {
	if(m_head >= m_tail) {
	return m_head - m_tail;
	}
	return (m_bufferSize  - m_tail) + m_head + 1; /* we wrapped around use this corrected formula */
}

void CircularBuffer::flush() {
	m_tail = m_head;
}

void CircularBuffer::bufferInit() {
	unsigned int i;
	for(i = 0; i < m_bufferSize ;++i) {
		*(m_data + i) = 0;
	}
}
unsigned int CircularBuffer::getHeadIndex() {
	return m_head;
}

unsigned int CircularBuffer::getTailIndex() {
	return m_tail;
}

unsigned char CircularBuffer::getByte() {
	if(bufferSize() == 0) {
		qDebug() << "problem getByte() called when the buffer was empty";
		return 0;
	}
	unsigned char byte;
	byte = *(m_data + m_tail);
	m_tail++;
	if(m_tail > m_bufferSize) {
		m_tail = 0;
	}
	return byte;
}

void CircularBuffer::fillPayload(payloadVector& payload) {
	unsigned int i;
	unsigned char byte;
	for (i = m_tail; i != m_head; ) {
		byte = *(m_data + i);
		i++;
		payload.push_back(byte);
		if (i > m_bufferSize) {
			i = 0;
		}
	}
}

void CircularBuffer::RXFromBuffer(unsigned char *buf, unsigned int size) {
	unsigned int i;
	unsigned int j;
	unsigned char byte;
	for (i = m_tail, j = 0; i != m_head && size > j; i++, j++) {
		if (i > m_bufferSize) {
			i = 0;
		}
		byte = *(m_data + i);
		qDebug() << "RXFromBuffer TX'd " << byte;
		*(buf + j) = byte;
	}
	//consume
	m_tail = i;
}

void CircularBuffer::bufferBarf() {
	unsigned int i;
	QVector<unsigned char> barf;
	for(i = 0; m_bufferSize > i; i++) {
		barf.push_back((unsigned char) *(m_data + i));
	}
	qDebug() << "Barfing circular buffer";
	qDebug() << barf;
}

void CircularBuffer::bufferSaveLastAsFirst() {
	if(m_head > 0) {
		m_tail = m_head - 1;
	} else {
		m_tail = m_bufferSize;
	}
}

} /* namespace IPDS */
