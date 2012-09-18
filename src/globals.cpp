/*
 * globals.c
 *
 *  Created on: Dec 7, 2011
 *      Author: seank
 */

#include "inc/globals.h"


namespace IPDS {

QWaitCondition g_readBlock;
QWaitCondition g_writeBlock;
//QWaitCondition g_busyReading;
//QWaitCondition g_busyWriting;
QMutex	g_readMutex;
QMutex g_readShutdownMutex;
QMutex g_writeShutdownMutex;

int g_readError;

} /* namespace IPDS */
