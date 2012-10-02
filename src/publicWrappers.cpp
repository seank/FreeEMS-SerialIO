/*
 * publicWrappers.cpp
 *
 *  Created on: Aug 16, 2012
 *      Author: seank
 */


/* ############### WRAPPERS FOR PUBLIC INTERFACE ######### */

SerialIO::SerialIO() : d_ptr(new SerialIOPrivate) {

}

SerialIO::~SerialIO() {
	qDebug() << "SerialIO::~SerialIO() called";
	delete d_ptr;
}

int SerialIO::setupPort(int baud, int databits, const QString& parity, int stop) {
	return d_ptr->setupPort(baud, databits, parity, stop);
}

void SerialIO::flushRX() {
	return d_ptr->flushRX();
}

void SerialIO::setMode(QString& mode) {
	return d_ptr->setMode(mode);
}

void SerialIO::openPort(QString portName) {
	return d_ptr->openPort(portName);
}

bool SerialIO::isOpen() {
	return d_ptr->isOpen();
}

int SerialIO::readData(unsigned char* buf, size_t numBytes) {
	return d_ptr->readData(buf, numBytes);
}

void SerialIO::addByte(unsigned char& byte) {
	return d_ptr->addByte(byte);
}

void SerialIO::writeData(const void* data, size_t size) {
	return d_ptr->writeData(data, size);
}

void SerialIO::setDataMode(QString& mode) {
	return d_ptr->setDataMode(mode);
}

bool SerialIO::isCommunicating() {
	return d_ptr->isCommunicating();
}

void SerialIO::communicate() {
	return d_ptr->communicate();
}

void SerialIO::closePort() {
	return d_ptr->closePort();
}

void SerialIO::run() {
	return d_ptr->run();
}

void SerialIO::writeString(QString&) {
	return d_ptr->run();
}

void SerialIO::processRXError(int RXErrorNumber) {
	return d_ptr->processRXError(RXErrorNumber);
}

void SerialIO::receivedRXBlock(payloadVector payload) {
	return d_ptr->receivedRXBlock(payload);
}

void SerialIO::receivedRXPacket(payloadVector packet) {
	return d_ptr->receivedRXPacket(packet);
}

void SerialIO::processTXError(int RXErrorNumber) {
	return d_ptr->processTXError(RXErrorNumber);
}
