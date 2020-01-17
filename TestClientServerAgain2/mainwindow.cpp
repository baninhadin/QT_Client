#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_connect_clicked()
{
    socket->bind(QHostAddress::AnyIPv4, ui->spinBox->value(), QUdpSocket::ShareAddress);
    socket->joinMulticastGroup(QHostAddress("224.16.80.80"));
}

void MainWindow::readyRead()
{
    if(socket->hasPendingDatagrams())
    {
    QByteArray buffer;
    QHostAddress sender;
    buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size(), &sender);
    ui->listWidget->addItem(buffer + " from IP : "+ sender.toString());
    }
    else
    {
        ui->listWidget->addItem("No Pending Datagram");
    }
}
