#include "escposserial.h"


//IbisIpSubscriberOnePublisher::IbisIpSubscriberOnePublisher(QString serviceName,QString structureName,QString version,QString serviceType, int portName) : IbisIpSubscriber(serviceName,structureName, version, serviceType, portName)


EscPosSerial::EscPosSerial()
{
 //   serialSender.start();
}

EscPosSerial::~EscPosSerial()
{
    serialSender.stop();
}


void EscPosSerial::startPort()
{
    serialSender.start();
}




void EscPosSerial::send(QByteArray data)
{
    serialSender.sendToPortNew(data);
}

