/*
 * AsyncRead.cpp
 *
 *  Created on: Nov 15, 2011
 *      Author: seank
 */

#include "inc/AsyncRead.h"

namespace IPDS {

AsyncRead::AsyncRead(int *FD, CircularBuffer *buffer) {
	m_FD = FD;
	m_readBuffer = buffer;
	m_bytesExpected = 0;
	m_nextIsEscaped = false;
	m_mode = "FREEEMS";
	m_numConsecutiveGarbageBytes = 0;
	m_numPacketsRX = 0;
	m_numGarbageBytes = 0;
	m_numTotalRXBytes = 0;
}

AsyncRead::~AsyncRead() {
	// TODO Auto-generated destructor stub
}

void IPDS::AsyncRead::shutdownThread() {
	qDebug("Shutdown request AsyncRead");
	g_readShutdownMutex.lock();
	m_shutdown = true;
	g_readShutdownMutex.unlock();
	qDebug() << this->currentThreadId();
//	this->exit();
}

/* thread run overload */
void IPDS::AsyncRead::run() {
//	m_shutdown = false;
	int result = 0;
	unsigned char byte = 0;

// TODO code to consider
//	while (m_shutdown == false)
//	{
//	    do
//	    {
//	          result = read(*m_FD, &byte, 1);
//	    }
//	   while (result == -1 && errno == EWOULDBLOCK);
//	   if (result == 1)
//	         process(byte);
//	   else
//	   {
//	          // other error
//	   }
//	   sleep(1);
//	}

	//for(g_readShutdownMutex.lock(); m_shutdown == false; g_readShutdownMutex.lock()) {
	while(true) {
//		g_readShutdownMutex.unlock();
		if (*m_FD == -1) {
			//file descriptor went bad on us
			qDebug("HES DEAD JIM, PORT DIED");
			return; //terminate thread
			//emit RXError(INVALID_FD);
		} else {
			result = read(*m_FD, &byte, 1);  //sites here forever until data comes in on the serial port
			if (result > 0) {
				//emit RXByte(byte);
				processByte(byte);
			} else if (result == 0) {
				// read zero bytes but did not error
				qDebug("READ() gave us 0, something must be wrong emitting error");
				emit RXError(BAD_FD);
			} else {
				// recieved some sort of error
				emit RXError(result);
			}
		}
	}
	g_readShutdownMutex.unlock();
}

void IPDS::AsyncRead::processByte(unsigned char& byte) {
	m_readBuffer->pushByte(byte);
	m_numTotalRXBytes++;
	payloadVector payload;
	if (m_mode == "FREEEMS") {
		if (m_insidePacket == false) {
			if ((byte == START_BYTE) && (m_lastByte != ESCAPE_BYTE)) {
				qDebug("start of packet detected");
				m_numConsecutiveGarbageBytes = 0;
				m_insidePacket = true;
				m_readBuffer->bufferSaveLastAsFirst();
			} else {
				qDebug("read %x outside of packet last byte was %x", byte,
						m_lastByte);
				++m_numConsecutiveGarbageBytes;
				if (m_numConsecutiveGarbageBytes > 156) { //todo clean/rethink
					qDebug("max number of out of packet bytes reached terminating reader");
					m_readBuffer->bufferBarf();
				}
//				m_readBuffer->bufferBarf();
			}
		} else if (m_insidePacket == true) {
			if ((byte == STOP_BYTE) && (m_lastByte != ESCAPE_BYTE)) {
				m_insidePacket = false;
				m_numPacketsRX++;
				qDebug("END of packet detected");
				m_readBuffer->fillPayload(payload);
//				qDebug("size of packet is %i", m_readBuffer->bufferSize());
				emit
				RXPacket(payload);
//				m_readBuffer->bufferBarf();
				m_readBuffer->flush();
			}
		}
	} else if (m_mode == "RAW") {
		//TODO just push bytes to the buffer
		//maybe emit an error if the buffer overruns
		qDebug("a byte just came in the serial port in raw mode");
		g_readBlock.wakeAll();
	} else {
		if (m_bytesExpected > 0) {
			if (m_readBuffer->bufferSize() == m_bytesExpected) {
				m_readBuffer->fillPayload(payload);
				m_readBuffer->flush();
				emit RXBlock(payload);
			}
		} else {
			qDebug("read unexpected garbage on the line %x", byte);
		}
	}
	m_lastByte = byte;
}
void IPDS::AsyncRead::setExpectedBytes(unsigned int numBytes) {
	m_bytesExpected = numBytes;
}

void IPDS::AsyncRead::setMode(QString& mode) {
	m_mode = mode;
}

void IPDS::AsyncRead::flush() {
	m_readBuffer->flush();
}

} /* namespace IPDS */
