/*
 * globals.h
 *
 *  Created on: Dec 7, 2011
 *      Author: seank
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <QWaitCondition>
#include <QMutex>

namespace IPDS {

extern QWaitCondition g_readBlock;
extern QWaitCondition g_writeBlock;
//extern QWaitCondition g_busyReading;
//extern QWaitCondition g_busyWriting;
extern QMutex g_readMutex;
extern QMutex g_readShutdownMutex;
extern QMutex g_writeShutdownMutex;

} /* namespace IPDS */
#else
#warning "GLOBALS_H_ already defined sort it out!"
#endif /* GLOBALS_H_ */
