#ifndef SERIALSENDER_H
#define SERIALSENDER_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPort>



#include <QDebug>
#include <QCoreApplication>
#include <QTimer>


class SerialSender: public QObject
{
        Q_OBJECT

public:
    SerialSender();
    ~SerialSender();

    void sendToPortNew(QString obsah);
    void vypisStringPoBytech(QString vstup);
    void portStop(QSerialPort &port);

    QString serialPortName() const;
    void setSerialPortName(const QString &newSerialPortName);

    void start();
    void stop();

    int delayBetweenMessagesMs() const;
    void setDelayBetweenMessagesMs(int newDelayBetweenMessagesMs);

    void sendToPortNew(QByteArray obsah);
private slots:
    void slotBytesWritten();

    void slotDelayBetweenMessagesTimeout();
protected:
    //QString nahradDiakritiku(QString vstup);

    QTimer casovac;

    int mDelayBetweenMessagesMs=700;

    QString mSerialPortName="COM6";
    //instance knihoven


    /*          nove               */
    QSerialPort serial;

    bool odesilaniBezi=false;

   // QVector<QString> zasobnikZprav;
    QVector<QByteArray> zasobnikZprav;
    void writeStringToPort(QSerialPort &port, QByteArray content);
    void startPortu(QSerialPort &port);
signals:
    //new
    void timeout(const QString &s);
};


#endif // SERIALSENDER_H
