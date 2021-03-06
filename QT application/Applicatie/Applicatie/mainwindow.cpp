#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialport.h"

#include <QMessageBox>
#include <QDebug>
#include <QIODevice>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    portList = QSerialPortInfo::availablePorts();
    for (int i = 0; i < portList.size(); ++i) {
        ui->cmbComPorten->insertItem(1, portList.at(i).portName());
    }

    QString url = QString(R"(C:\Users\sande\Documents\Bedraadlozen\QT application\Applicatie\Applicatie\Bedraadloos.png)");
    QPixmap img(url);
    img.setDevicePixelRatio(4);
    ui->label->setPixmap(img);
}

MainWindow::~MainWindow()
{
    if (serial->isOpen())
        serial->close();
    delete serial;
    delete ui;
}

void MainWindow::openSerialPort(){
    if(serial == nullptr){
        serial = new QSerialPort();
        serial->setPortName(ui->cmbComPorten->currentText());
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data7);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        if(serial->open(QIODevice::ReadWrite)){
             Serialport serialport(serial);
             ui->btnConnect->setEnabled(false);
             ui->cmbComPorten->setEnabled(false);
        }else{
            QMessageBox::critical(this, tr("Error"), serial->errorString());
        }
     }
}

void MainWindow::on_btnConnect_clicked()
{
    openSerialPort();
}

void MainWindow::on_btnLed1_clicked()
{
    serial->write("\xff");
}

void MainWindow::on_btnLed2_clicked()
{
    serial->write("\xfe");
}

void MainWindow::on_btnLed3_clicked()
{
    serial->write("\xfd");
}
