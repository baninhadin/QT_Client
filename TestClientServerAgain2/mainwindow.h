#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QString>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_connect_clicked();
    void readyRead();
    void onReadyRead();

private:
    Ui::MainWindow *ui;
    QUdpSocket *socket;
    QTcpSocket _socket;
    char header, command, style, cnn_status;
    int n_robot_aktif, n_robot_dekat_bola, n_robot_dapat_bola, bola_x_pada_lapangan, bola_y_pada_lapangan;
};
#endif // MAINWINDOW_H
