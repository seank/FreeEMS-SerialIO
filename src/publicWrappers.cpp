/*
 * publicWrappers.cpp
 *
 *  Created on: Aug 16, 2012
 *      Author: seank
 */


/* ############### WRAPPERS FOR PUBLIC INTERFACE ######### */

SerialIO::SerialIO() : d(new SerialIOPrivate) {

}

SerialIO::~SerialIO() {
	//delete d;
}

int SerialIO::setupPort(int baud, int databits, const QString& parity, int stop) {
	return d->setupPort(baud, databits, parity, stop);
}

void SerialIO::flushRX() {
	return d->flushRX();
}

void SerialIO::setMode(QString& mode) {
	return d->setMode(mode);
}

void SerialIO::openPort(QString portName) {
	return d->openPort(portName);
}

bool SerialIO::isOpen() {
	return d->isOpen();
}

int SerialIO::readData(unsigned char* buf, size_t numBytes) {
	return d->readData(buf, numBytes);
}

void SerialIO::addByte(unsigned char& byte) {
	return d->addByte(byte);
}

void SerialIO::writeData(const void* data, size_t size) {
	return d->writeData(data, size);
}

void SerialIO::setDataMode(QString& mode) {
	return d->setDataMode(mode);
}

bool SerialIO::isCommunicating() {
	return d->isCommunicating();
}

void SerialIO::communicate() {
	return d->communicate();
}

void SerialIO::closePort() {
	return d->closePort();
}

void SerialIO::run() {
	return d->run();
}

void SerialIO::writeString(QString&) {
	return d->run();
}

void SerialIO::processRXError(int RXErrorNumber) {
	return d->processRXError(RXErrorNumber);
}

void SerialIO::receivedRXBlock(payloadVector payload) {
	return d->receivedRXBlock(payload);
}

void SerialIO::receivedRXPacket(payloadVector packet) {
	return d->receivedRXPacket(packet);
}

void SerialIO::processTXError(int RXErrorNumber) {
	return d->processTXError(RXErrorNumber);
}
