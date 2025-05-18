#include "serialsender.h"

SerialSender::SerialSender()
{
    connect(&serial, &QSerialPort::bytesWritten ,this,&SerialSender::slotBytesWritten );
    casovac.setInterval(mDelayBetweenMessagesMs);
    casovac.setSingleShot(true);
    connect(&casovac,&QTimer::timeout, this, &SerialSender::slotDelayBetweenMessagesTimeout);
    // startPortu(serial);
}


SerialSender::~SerialSender()
{
    //portStop(serial);
}



QString SerialSender::serialPortName() const
{
    return mSerialPortName;
}

void SerialSender::setSerialPortName(const QString &newSerialPortName)
{
    mSerialPortName = newSerialPortName;
}









/* ----------------  nove --------------------*/
void SerialSender::slotBytesWritten()
{
    qDebug() << Q_FUNC_INFO;
    casovac.start();
}


void SerialSender::writeStringToPort(QSerialPort &port,QByteArray content)
{
    qDebug() << Q_FUNC_INFO <<" length:"<<content.length()<< " "<<content;
    const QByteArray contentByteArray = content;
    port.write(contentByteArray);

    /*
    if (port.waitForBytesWritten(m_waitTimeout))
    {


        // read response
        if (serial.waitForReadyRead(currentWaitTimeout))
        {
            QByteArray responseData = serial.readAll();
            while (serial.waitForReadyRead(10))
                responseData += serial.readAll();

            const QString response = QString::fromUtf8(responseData);


    }
    else
    {
        emit timeout(tr("Wait write request timeout %1")
                     .arg(QTime::currentTime().toString()));
    }
    */

}




//vstupni funkce
void SerialSender::sendToPortNew(QString obsah)
{
    qDebug() << Q_FUNC_INFO;

    QString currentPortName=mSerialPortName;


    qDebug()<<"port "<<currentPortName<< " obsah "<<obsah.length()<<" "<<obsah;

    //vypisStringPoBytech(obsah);

    if (currentPortName.isEmpty()) {
        qDebug()<<"No port name specified";
        return;
    }


    zasobnikZprav.push_back(obsah.toLatin1());


    if(odesilaniBezi==false)
    {
        qDebug()<<"menim odesilani bezi na true";
        odesilaniBezi=true;
        slotBytesWritten();
    }
    else
    {
        qDebug()<<"odesilani uz bezelo";
    }



}

void SerialSender::sendToPortNew(QByteArray obsah)
{
    qDebug() << Q_FUNC_INFO;

    QString currentPortName=mSerialPortName;



    qDebug()<<"port "<<currentPortName<< " obsah "<<obsah.length()<<" "<<obsah;

     qDebug().noquote()<<"port "<<currentPortName<< " obsah "<<obsah.length()<<" "<<obsah;

    //vypisStringPoBytech(obsah);

    if (currentPortName.isEmpty()) {
        qDebug()<<"No port name specified";
        return;
    }


    zasobnikZprav.push_back(obsah);


    if(odesilaniBezi==false)
    {
        qDebug()<<"menim odesilani bezi na true";
        odesilaniBezi=true;
        slotBytesWritten();
    }
    else
    {
        qDebug()<<"odesilani uz bezelo";
    }



}


void SerialSender::slotDelayBetweenMessagesTimeout()
{
    qDebug() << Q_FUNC_INFO;

    qDebug()<<"byty jsou zapsany";
    if(!zasobnikZprav.isEmpty())
    {
        QByteArray aktualniPolozka=zasobnikZprav.first();
        zasobnikZprav.removeFirst();

        writeStringToPort(serial,aktualniPolozka);
        qDebug()<<"v zasobniku zbylo "<<zasobnikZprav.count();
    }
    else
    {
        qDebug()<<"zasobnik je uz prazdny";
        odesilaniBezi=false;
    }
}

int SerialSender::delayBetweenMessagesMs() const
{
    return mDelayBetweenMessagesMs;
}

void SerialSender::setDelayBetweenMessagesMs(int newDelayBetweenMessagesMs)
{
    mDelayBetweenMessagesMs = newDelayBetweenMessagesMs;
    casovac.setInterval(mDelayBetweenMessagesMs);
}



void SerialSender::start()
{
    startPortu( serial );
}


void SerialSender::stop()
{
    portStop(   serial);
}

// 58 mm mini printer
void SerialSender::startPortu(QSerialPort &port)
{

    qDebug() << Q_FUNC_INFO;
    port.setBaudRate(115200);
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);
    port.setFlowControl(QSerialPort::NoFlowControl);

    //serial.close();
    port.setPortName("COM5");

    if (!port.open(QIODevice::ReadWrite))
    {
        qDebug()<<(tr("Can't open %1, error code %2")
                         .arg(port.portName()).arg(port.error()));
        return;
    }
}

/* Posiflex
void SerialSender::startPortu(QSerialPort &port)
{

    qDebug() << Q_FUNC_INFO;
    port.setBaudRate(38400);
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);
    port.setFlowControl(QSerialPort::NoFlowControl);

    //serial.close();
    port.setPortName("COM3");

    if (!port.open(QIODevice::ReadWrite))
    {
        qDebug()<<(tr("Can't open %1, error code %2")
                         .arg(port.portName()).arg(port.error()));
        return;
    }
}
*/

void SerialSender::portStop(QSerialPort &port)
{
    port.close();
    odesilaniBezi=false;
}

void SerialSender::vypisStringPoBytech(QString vstup)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray poleCharu=vstup.toLatin1();
    for(int i=0;i<poleCharu.size();i++)
    {
        qDebug()<<"i="<<i<<" "<<QString::number(poleCharu[i],16);//<<QString::number(test[i],16);
    }
}
