#ifndef ESCPOSSERIAL_H
#define ESCPOSSERIAL_H

#include "escposprinter.h"
#include "IbisSender/serialsender.h"

class EscPosSerial : public EscPosPrinter
{
public:
    explicit EscPosSerial();
    SerialSender serialSender;

    ~EscPosSerial();
    void startPort();
    void send(QByteArray data);
};

#endif // ESCPOSSERIAL_H
