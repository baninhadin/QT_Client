#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), _socket(this)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
//    _socket.connectToHost(QHostAddress("127.16.80.110"), 28097);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead()
{
    if(_socket.waitForConnected())
    {
    QByteArray datas = _socket.readAll();
    qDebug() << "Connected : " << datas;
    _socket.write(QByteArray("ok !\n"));
    }
}

void MainWindow::on_button_connect_clicked()
{
//    socket->bind(QHostAddress::AnyIPv4, ui->spinBox->value(), QUdpSocket::ShareAddress);
//    socket->joinMulticastGroup(QHostAddress("224.16.80.80"));
//    auto data = ui->lineEdit->text().toLatin1();
//    QHostAddress host = QHostAddress(QString(data));
//    socket->connectToHost(QHostAddress("192.168.1.11"), 28097);
//    qDebug() << QString("Connecting with " ) << QString(data);
    socket->bind(ui->spinBox->value(), QUdpSocket::ShareAddress);
//    socket->joinMulticastGroup(QHostAddress("224.16.80.80"));
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
