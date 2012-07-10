/*
 * SerialIO.cpp
 *
 *  Created on: Nov 15, 2011
 *      Author: seank
 */

#include "inc/SerialIO.h"

namespace IPDS {

SerialIO::SerialIO(): asyncReader(&m_FD, &m_readBuffer), asyncWriter(&m_FD, &m_writeBuffer), m_readBuffer(8196), m_writeBuffer(8196) {
	TXBytesLeft = 0;
	m_isCommunicating = false;
	m_isConfigured = false;
	m_numBytesExpected = 1;
	m_readBlockMS = 2000; //default to 2000ms before read() times out
	//QString mode = "FREEEMS";
	QString mode = "RAW";
	asyncReader.setMode(mode);
	/* setup signals and slots */
	qRegisterMetaType<payloadVector>("payloadVector");
	QObject::connect(&asyncReader, SIGNAL( RXBlock(payloadVector) ), this, SLOT( receivedRXBlock(payloadVector) ));
	QObject::connect(&asyncReader, SIGNAL( RXPacket(payloadVector) ), this, SLOT( receivedRXPacket(payloadVector)) );
	QObject::connect(&asyncReader, SIGNAL( RXError(int)), this, SLOT( processRXError(int) ));
	QObject::connect(&asyncWriter, SIGNAL( TXError(int)), this, SLOT( processTXError(int) ));
}

SerialIO::~SerialIO() {
	// TODO Auto-generated destructor stub
}

int IPDS::SerialIO::setupPort(int baudrate, int databits, const QString& parity, int stop) {
#ifdef __WIN32__
	win32_setup_serial_params(_fd, baud, 8, NONE, 1);
	return 0;
#else
	   struct termios newtio;
	   //memset(&newtio, 0, sizeof(newtio));
	   if (tcgetattr(m_FD, &m_oldtio)!=0) {
	           std::cerr<<"tcgetattr() 2 failed"<<std::endl;
	   }
	   if (tcgetattr(m_FD, &newtio)!=0)
	   {
	      std::cerr<<"tcgetattr() 3 failed"<<std::endl;
	   }
	   speed_t _baud=0;
	   switch (baudrate)
	   {
	#ifdef B0
	   case      0: _baud=B0;     break;
	#endif

	#ifdef B50
	   case     50: _baud=B50;    break;
	#endif
	#ifdef B75
	   case     75: _baud=B75;    break;
	#endif
	#ifdef B110
	   case    110: _baud=B110;   break;
	#endif
	#ifdef B134
	   case    134: _baud=B134;   break;
	#endif
	#ifdef B150
	   case    150: _baud=B150;   break;
	#endif
	#ifdef B200
	   case    200: _baud=B200;   break;
	#endif
	#ifdef B300
	   case    300: _baud=B300;   break;
	#endif
	#ifdef B600
	   case    600: _baud=B600;   break;
	#endif
	#ifdef B1200
	   case   1200: _baud=B1200;  break;
	#endif
	#ifdef B1800
	   case   1800: _baud=B1800;  break;
	#endif
	#ifdef B2400
	   case   2400: _baud=B2400;  break;
	#endif
	#ifdef B4800
	   case   4800: _baud=B4800;  break;
	#endif
	#ifdef B7200
	   case   7200: _baud=B7200;  break;
	#endif
	#ifdef B9600
	   case   9600: _baud=B9600;  break;
	#endif
	#ifdef B14400
	   case  14400: _baud=B14400; break;
	#endif
	#ifdef B19200
	   case  19200: _baud=B19200; break;
	#endif
	#ifdef B28800
	   case  28800: _baud=B28800; break;
	#endif
	#ifdef B38400
	   case  38400: _baud=B38400; break;
	#endif
	#ifdef B57600
	   case  57600: _baud=B57600; break;
	#endif
	#ifdef B76800
	   case  76800: _baud=B76800; break;
	#endif
	#ifdef B115200
	   case 115200: _baud=B115200; break;
	#endif
	#ifdef B128000
	   case 128000: _baud=B128000; break;
	#endif
	#ifdef B230400
	   case 230400: _baud=B230400; break;
	#endif
	#ifdef B460800
	   case 460800: _baud=B460800; break;
	#endif
	#ifdef B576000
	   case 576000: _baud=B576000; break;
	#endif
	#ifdef B921600
	   case 921600: _baud=B921600; break;
	#endif
	   default:
	      _baud=B115200;
	      break;
	   }
	   /* RX and TX are presumed to be the same */
	   cfsetospeed(&newtio, (speed_t)_baud);
	   cfsetispeed(&newtio, (speed_t)_baud);
	   /* We generate mark and space parity ourself. */
	   if (databits == 7 && (parity=="mark" || parity == "space"))
	   {
	      databits = 8;
	   }
	   switch (databits)
	   {
	   case 5:
	      newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS5;
	      break;
	   case 6:
	      newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS6;
	      break;
	   case 7:
	      newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS7;
	      break;
	   case 8:
	   default:
	      newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS8;
	      break;
	   }
	   newtio.c_cflag |= CLOCAL | CREAD;
	   //parity
	   if (parity == "even") {
	      newtio.c_cflag |= PARENB;
	   } else if (parity == "odd") {
	      newtio.c_cflag |= (PARENB | PARODD);
	   } else if (parity == "none") {
		   newtio.c_cflag &= ~(PARENB | PARODD);
	   } else {
		   qDebug("Parity not specified defaulting to none.");
		   newtio.c_cflag &= ~(PARENB | PARODD);
	   }
	   //disable hardware handshake
	   newtio.c_cflag &= ~CRTSCTS;
	   //configure stopbits
	   if (stop == 2)
	   {
	      newtio.c_cflag |= CSTOPB;
	   }
	   else
	   {
	      newtio.c_cflag &= ~CSTOPB;
	   }
	   newtio.c_iflag=IGNBRK;
	   //disable software handshake
	   newtio.c_iflag &= ~(IXON|IXOFF|IXANY);
	   newtio.c_lflag=0;
	   newtio.c_oflag=0;
	   //newtio.c_cc[VTIME]=1;
	   //newtio.c_cc[VMIN]=60;
	   newtio.c_cc[VTIME]=2;
	   newtio.c_cc[VMIN]=1;
	   tcflush(m_FD, TCIFLUSH);
	   if (tcsetattr(m_FD, TCSANOW, &newtio)!=0)
	   {
	      std::cerr<<"tcsetattr() 1 failed"<<std::endl;
	   }
	   int mcs=0;
	   ioctl(m_FD, TIOCMGET, &mcs);
	   mcs |= TIOCM_RTS;
	   ioctl(m_FD, TIOCMSET, &mcs);
	   if (tcgetattr(m_FD, &newtio)!=0)
	   {
	      std::cerr<<"tcgetattr() 4 failed"<<std::endl;
	   }
	   /* disable hardware handshake */
	   newtio.c_cflag &= ~CRTSCTS;
	   if (tcsetattr(m_FD, TCSANOW, &newtio)!=0)
	   {
	      std::cerr<<"tcsetattr() 5 failed"<<std::endl;
	   }
#endif
	   return 1;
}

void IPDS::SerialIO::openPort(QString portName) {
	m_portName = portName;
	#ifdef __WIN32__
	m_FD = open(port_name, O_RDWR | O_BINARY );
#else
	/* NON-block open, then turn to blocking via fcntl so it works
	 nicely on linux and OS-X.  this MUST be done this way because
	 in OS-X some serial devices will BLOCK on open waiting for the
	 control lines to get into the state it wants, thus blocking
	 open() indefinitely.  Thus we open nonblocking then flip the bit
	 afterwards, as termios will set things up the way we want..
	 */
//	_FD = open(_portName, O_RDWR | O_NOCTTY | O_NONBLOCK);
	m_FD = open(m_portName.toUtf8().constData(), O_RDWR | O_NOCTTY | O_NDELAY);
//	fcntl(m_FD, ~O_NONBLOCK);
	fcntl(m_FD, F_SETFL, 0);

#endif
	m_isOpen = m_FD != -1 ? true : false;
	m_isCommunicating = m_isOpen;
}

bool IPDS::SerialIO::isOpen() {
	return m_isOpen;
}

bool IPDS::SerialIO::isCommunicating() {
	return m_isCommunicating;
}

void IPDS::SerialIO::communicate() {
	if(m_isOpen) {
		//asyncReader.m_communicating = &_isCommunicating;
		//asyncWriter._communicating = &_isCommunicating;
		asyncReader.start();
		asyncWriter.start();
	} else {
		printf("Error can't start port not open");
	}
}

void IPDS::SerialIO::processRXError(int RXErrorNumber) {
	//TODO act appropriately for the error for now just terminate
	printf("RX Error %i \n", RXErrorNumber);
	//if(RXErrorNumber == BAD_FD ||  RXErrorNumber == INVALID_FD) {
	closePort();
	//}
}

void IPDS::SerialIO::processTXError(int RXErrorNumber) {
	//TODO act appropriately for the error for now just terminate
	printf("TX Error %i \n", RXErrorNumber);
	//if(RXErrorNumber == BAD_FD ||  RXErrorNumber == INVALID_FD) {
	closePort();
	//}
}

void IPDS::SerialIO::receivedRXBlock(payloadVector payload) {
	qDebug("RXblock callback answered");
	qDebug() << payload;

	emit readBytesFinished(payload);
	unsigned char test = 0x0d;
	writeData(&test, 1);
}

void IPDS::SerialIO::receivedRXPacket(payloadVector packet) {
//	packet.push_back('h');
//	m_readBuffer.fillVector(test, head, tail);
	qDebug("SerialIO RXPacket callback answered");
	qDebug() << packet;

	emit readPacketFinished(packet);

//	unsigned char test = 0x0d;
//	writeData(&test, 1);
}

//void IPDS::SerialIO::flushRX() {
//	asyncReader.m_readBuffer->flush();
//}

void IPDS::SerialIO::closePort() { //maybe rename to shutdown
	if (m_FD !=-1) {
		tcsetattr(m_FD, TCSANOW, &m_oldtio);
	}
	m_isCommunicating = false;
	m_isOpen = false;
	qDebug("Waiting for threads to finish");
	if (asyncWriter.isRunning()) {
		asyncWriter.shutdownThread();
		asyncWriter.wait();
	}
	if (asyncReader.isRunning()) {
		asyncReader.terminate();
		//asyncReader.shutdownThread();
		//asyncReader.wait(); //wait 10ms
		//if(asyncReader.isRunning()) {
		//	asyncReader.terminate(); // if its still running kill it!
		//}
	}
	qDebug("Done waiting for threads");
	close(m_FD);
	m_FD = -1;
	qDebug("closed port");
}

void IPDS::SerialIO::addByte(unsigned char& byte) {
	m_readBuffer.pushByte(byte);
	m_numBytesProcessed++;
	if (m_numBytesExpected == m_numBytesProcessed) {
		if (m_dataMode == "SM") {
			//process SM response
		} else if (m_dataMode == "FREEEMS") {
			//TODO process FREEEMS response
		}
	}
}

void IPDS::SerialIO::writeData(const void* data, size_t bufferSize) {
	qDebug("Performing a write");
	unsigned int i;
	for(i = 0; bufferSize > i; i++) {
		m_writeBuffer.pushByte(*(static_cast<const unsigned char*>(data) + i));
	}
	g_writeBlock.wakeAll();
}

void IPDS::SerialIO::setMode(QString& mode) {
	asyncReader.setMode(mode);
}

void IPDS::SerialIO::flushRX() {
	asyncReader.flush();
}

int IPDS::SerialIO::readData(unsigned char* buf, size_t numBytes) {
//	qDebug("Performing a read...");
	unsigned int i;
	unsigned int lastNumBytes;
	unsigned int currentNumBytes;
	for (i = 0, lastNumBytes = 0, currentNumBytes = 0;
			numBytes > (currentNumBytes = m_readBuffer.bufferSize());) {
//		qDebug("buffer smaller than requested(have %i but need %i) read size waiting....", m_readBuffer.bufferSize(), numBytes);
		g_readMutex.lock();
		if (g_readBlock.wait(&g_readMutex, 1) == false) { // wait for 1ms or until we are woke up by a byte coming in
			if (lastNumBytes == currentNumBytes) {
				i++; //we have timed out
			} else {
				i = 0;
			}
		}
		g_readMutex.unlock();
		if (i > m_readBlockMS) { //TODO make configurable
			qDebug() << "Read Incomplete: We timed out, readData() is returning " <<  currentNumBytes << " of"
					<< numBytes << " requested bytes";
			return currentNumBytes;
		}
		lastNumBytes = currentNumBytes;
	}
	m_readBuffer.RXFromBuffer(buf, numBytes);
	return numBytes;
}

void IPDS::SerialIO::run() {
	//TODO make signal and slot connections if this object proves to be useful running in its own thread
	exec();
}

void IPDS::SerialIO::setDataMode(QString& mode) {
	m_dataMode = mode;
}
} /* namespace IPDS */
