#include <QtCore>
#include <QCoreApplication>
#include <CircularBuffer.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int i, j;
    unsigned char c;


    /* If a value is stored ouside it's allocated area it may crash at the time of the write
     * or when delete is called.
     */
	for (j = 0; j < 20000; j++) {
		IPDS::CircularBuffer *cBTest = new IPDS::CircularBuffer(8196);
		for (i = 0, c = 0; i < j; ++i, ++c) {
			cBTest->pushByte(c);
			if (i % 2)
				c = cBTest->getByte();
		}
		qDebug() << "About to delete the " << j << " iteration of this test.";
		delete cBTest;
	}
	return 1;
   // return a.exec();
}

