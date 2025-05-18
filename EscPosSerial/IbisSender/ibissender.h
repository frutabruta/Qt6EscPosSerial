#ifndef IBISSENDER_H
#define IBISSENDER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPort>



#include <QDebug>
#include <QCoreApplication>
#include <QTimer>



#include "serialsender.h"



class IbisSender: public SerialSender
{
    Q_OBJECT
public:
    IbisSender();
    ~IbisSender();

    QString sendTelegram(QString puvodniPrikaz);

    //nove


    void start();

    char checkSumCreate(QString puvodniPrikaz, QString &output);


private slots:



private:
    //QString nahradDiakritiku(QString vstup);





    QString mSerialPortName="COM5";
    //instance knihoven


    /*          nove               */
    QSerialPort serial;



    QVector<QString> zasobnikZprav;


    void startPortu(QSerialPort &port);
signals:
    //new
    void timeout(const QString &s);
};

#endif // IBISSENDER_H
