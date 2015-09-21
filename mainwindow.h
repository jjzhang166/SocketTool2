#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stdafx.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    //void on_actionUdpServer_triggered();
    //void on_actionUdpClient_triggered();
    void on_actionUdpSocket_triggered();
    void on_actionUdpGroup_triggered();

    //void udpServerCreated(QUdpSocket* udpSocket);
    //void udpClientCreated(QUdpSocket* udpSocket, const QString& peerAddress, const int& peerPort);
    void udpSocketCreated(QUdpSocket* udpSocket);
    void multicastCreated(QUdpSocket* udpSocket, const QString& multicastAddress);
    void soketReadyRead(QAbstractSocket* s);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
