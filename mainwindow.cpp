#include "mainwindow.h"
#include "EscPosSerial/escposprinter.h"
#include "ui_mainwindow.h"
#include <QBuffer>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    QBuffer b;
    b.open(QBuffer::ReadWrite);


    p.start(&b);

    //EscPosPrinter p(&b);

    // Init(reset) the printer and set some encoding
    p << EscPosPrinter::init << EscPosPrinter::EncodingPC850;

    // Print some text with some formatting options, if a plain string "foo" is sent
    // it won't be handled by QCodec, it will send as raw data.
    p << EscPosPrinter::PrintModes(EscPosPrinter::PrintModeDoubleWidth | EscPosPrinter::PrintModeDoubleHeight | EscPosPrinter::PrintModeEmphasized)
      << EscPosPrinter::JustificationCenter
      << QStringLiteral("Some Text");

    p << "\n";

    // Printing QRCodes
    p << EscPosPrinter::JustificationCenter << EscPosPrinter::PrintModes(EscPosPrinter::PrintModeNone)
      << EscPosPrinter::QRCode(EscPosPrinter::QRCode::Model2, 5, EscPosPrinter::QRCode::M, "https://github.com/ceciletti/escpos-qt") << "\n"
      << EscPosPrinter::JustificationLeft;







      startPortu(serial);
 serial.write(b.data());
    //serial.close();

}



void MainWindow::startPortu(QSerialPort &port)
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



void MainWindow::on_pushButton_exp_clicked()
{
    QBuffer b;
    b.open(QBuffer::ReadWrite);

    p.start(&b);


    // Print some text with some formatting options, if a plain string "foo" is sent
    // it won't be handled by QCodec, it will send as raw data.

    printerInit();

  //  textCenter(QDateTime::currentDateTime().toString() );


    textNormal("Pokladna No:2003396  EmTest");
    textNormal("prijmenou cestu Vam preje ridic Orsag");
    textNormal("CSAD Vsetin");
    textNormal("ICO: 60108843 DIC:   CZ60108843");
    textNormal("NEDELE   301-12-2007");
    textNormal("Cas: 16:29:23 Linka: 690850/3 CL: 92957/2003396");
    textNormal("ZDARMA");
    textNormal("Cena: 00.00, DPH 5% : 00.00,");
    textNormal("MHD OBycejne Jizdne");
    textNormal("^^^^^^^^^^^^^^^^^^^^");
    textNormal("Z :Tanvald,žel.st.");
    textNormal("DO:Tanvald,AS");



//    textNormal("příliš žluťoučký kůň úpěl ďábelské ódy");

    newLine();
  //  cut();

    p.serialSender.setSerialPortName("COM5");
    p.startPort();
    p.send(b.data());
   // p.serialSender.sendToPortNew(b.data());


}


void MainWindow::on_pushButton_serialStop_clicked()
{
    serial.close();
}


void MainWindow::qrCode()
{
    // Printing QRCodes
    p << EscPosPrinter::JustificationCenter << EscPosPrinter::PrintModes(EscPosPrinter::PrintModeNone)
      << EscPosPrinter::QRCode(EscPosPrinter::QRCode::Model2, 5, EscPosPrinter::QRCode::M, "https://github.com/ceciletti/escpos-qt") << "\n"
      << EscPosPrinter::JustificationLeft;
}

void MainWindow::printerInit()
{
        // Init(reset) the printer and set some encoding
  //   p << EscPosPrinter::init << EscPosPrinter::EncodingPC850;


        p << EscPosPrinter::init << EscPosPrinter::EncodingPC850;
}

void MainWindow::textCenter(QString input)
{
    p << EscPosPrinter::PrintModes(EscPosPrinter::PrintModeDoubleWidth | EscPosPrinter::PrintModeDoubleHeight | EscPosPrinter::PrintModeEmphasized)
    << EscPosPrinter::JustificationCenter
      << input;
    //<< QStringLiteral("input");
}


void MainWindow::textNormal(QString input)
{
    p  << EscPosPrinter::PrintModes(EscPosPrinter::PrintModeNone);
     p << EscPosPrinter::JustificationLeft
    << input;
    p << "\n";
    //<< QStringLiteral("input");
}



void MainWindow::newLine()
{
       p << "\n";
}

void MainWindow::cut()
{
    p.partialCut();
    //<< QStringLiteral("input");
}


