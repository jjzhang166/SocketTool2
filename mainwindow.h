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
    void on_actionTcpServer_triggered();
    void on_actionTcpClient_triggered();
    void on_actionUdpSocket_triggered();
    void on_actionUdpGroup_triggered();
    void on_actionRemoveSocket_triggered();
    void tcpServerCreated(QTcpServer* tcpServer);
    void tcpSocketCreated(QTcpSocket* tcpSocket, const QHostAddress& peerHost, const unsigned short& port);
    void udpSocketCreated(QUdpSocket* udpSocket);
    void multicastCreated(QUdpSocket* udpSocket, const QString& multicastAddress);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
