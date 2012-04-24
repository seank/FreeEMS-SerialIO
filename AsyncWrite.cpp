/*
 * AsyncWrite.cpp
 *
 *  Created on: Nov 16, 2011
 *      Author: seank
 */

#include "inc/AsyncWrite.h"
#include "inc/globals.h"

#include <stdio.h>

namespace IPDS {

AsyncWrite::AsyncWrite(int *FD, CircularBuffer *buffer) {
	_FD = FD;
	m_writeBuffer = buffer;
}

AsyncWrite::~AsyncWrite() {
	// TODO Auto-generated destructor stub
}

void IPDS::AsyncWrite::shutdownThread() {
	qDebug("Shutdown request AsyncWrite");
	g_writeShutdownMutex.lock();
	m_shutdown = true;
	g_writeShutdownMutex.unlock();
	qDebug() << this->currentThreadId();
}

void IPDS::AsyncWrite::run() {
	m_shutdown = false;
	int result = 0;
	unsigned char byte;
	QMutex writeMutex;
	for(g_writeShutdownMutex.lock(); m_shutdown == false; g_writeShutdownMutex.lock()) {
		g_writeShutdownMutex.unlock();
		while (m_writeBuffer->bufferSize() > 0 && m_shutdown == false) {
			byte = m_writeBuffer->getByte();
			result = write(*_FD, &byte, 1);
			if (result < 0) {
				qDebug("Error while trying to write to file descriptor, terminating writer");
				return;
			} else {
				qDebug("asyncWriter thread wrote byte to port %x", byte);
			}
		}
		writeMutex.lock();
		g_writeBlock.wait(&writeMutex, 100);
		writeMutex.unlock();
		//emit done
	}
	g_writeShutdownMutex.unlock();
}

} /* namespace IPDS */
