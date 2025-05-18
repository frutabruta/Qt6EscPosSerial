#include "ibissender.h"

IbisSender::IbisSender()
{

}


IbisSender::~IbisSender()
{

}


char IbisSender::checkSumCreate(QString puvodniPrikaz, QString &output)
{
    char zacatecniByte=0x7F;
    char ridiciZnak=0;
    char jeZnak=5;

    char hexridiciznak[2];

    QString prikaz=puvodniPrikaz+'\r';

    for (int k=0; k<prikaz.length(); k++)
    {
        if (prikaz[k]=='<')
        {
            jeZnak=0;
        }
        if (prikaz[k]=='>')
        {
            jeZnak=4;
        }
        switch (jeZnak)
        {
        case 0:
            jeZnak++;
            break;

        case 1:
            hexridiciznak[0]=prikaz[k].toLatin1() ;
            jeZnak++;
            break;

        case 2:
            hexridiciznak[1]=prikaz[k].toLatin1();
            jeZnak++;
            break;

        case 3:
            jeZnak++;
            break;
        case 4:
            ridiciZnak=int(strtol(hexridiciznak,NULL,16));
            zacatecniByte=zacatecniByte^ridiciZnak;
            output+=ridiciZnak;
            hexridiciznak[0]=0;
            hexridiciznak[1]=0;
            jeZnak++;
            break;
        case 5:
            zacatecniByte=zacatecniByte^prikaz[k].toLatin1();
            output+=prikaz[k];
            break;
        }

    }
    return zacatecniByte;
}

QString IbisSender::sendTelegram(QString puvodniPrikaz)
{

    qDebug() << Q_FUNC_INFO;
    //puvodniPrikaz=nahradDiakritiku(puvodniPrikaz);
    qDebug()<<puvodniPrikaz;

    QString prikaz =puvodniPrikaz;
    QString output="";


    char checkSum=checkSumCreate(prikaz,output);
    output+=checkSum;
    qDebug()<<"kontrolni soucet je "<<checkSum;
    qDebug()<<"output je:"<<output;
    sendToPortNew(output);
    //sendToPortOld(output);

    return output;

}

/* ----------------  nove --------------------*/


//vstupni funkce




void IbisSender::start()
{
    startPortu( serial );
}


void IbisSender::startPortu(QSerialPort &port)
{

    qDebug() << Q_FUNC_INFO;
    port.setBaudRate(1200);
    port.setDataBits(QSerialPort::Data7);
    port.setParity(QSerialPort::EvenParity);
    port.setStopBits(QSerialPort::TwoStop);
    port.setFlowControl(QSerialPort::NoFlowControl);

    //serial.close();
    serial.setPortName(mSerialPortName);

    if (!serial.open(QIODevice::ReadWrite))
    {
        qDebug()<<(tr("Can't open %1, error code %2")
                   .arg(serial.portName()).arg(serial.error()));
        return;
    }
}



