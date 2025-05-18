#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

#include "EscPosSerial/escposserial.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   QSerialPort serial;

    void startPortu(QSerialPort &port);

   EscPosSerial p;


   void newLine();
   private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_exp_clicked();



    void on_pushButton_serialStop_clicked();

private:
    Ui::MainWindow *ui;
    void qrCode();
    void printerInit();
    void textCenter(QString input);
    void textNormal(QString input);
    void cut();
};
#endif // MAINWINDOW_H
