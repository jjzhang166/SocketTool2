#ifndef TCPSOCKETOPERATEWIDGET_H
#define TCPSOCKETOPERATEWIDGET_H

#include <QWidget>
#include "stdafx.h"

namespace Ui {
class TcpSocketOperateWidget;
}

class TcpSocketOperateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpSocketOperateWidget(QWidget *parent = 0);
    ~TcpSocketOperateWidget();
    void setTcpSocket(QTcpSocket* tcpSocket, const QHostAddress& peerHost, const unsigned short& peerPort);

public slots:
    void on_pushButtonConnect_clicked();
    void on_pushButtonDisconnect_clicked();
    void socketConnected();
    void socketDisconnected();
    void socketError(QAbstractSocket::SocketError socketError);
    void socketStateChanged(QAbstractSocket::SocketState socketState);
    void soketReadyRead();
    void on_pushButtonSend_clicked();

private:
    Ui::TcpSocketOperateWidget *ui;
    QTcpSocket* m_socket;
    QHostAddress m_peerAddress;
    unsigned short m_peerPort;
};

#endif // TCPSOCKETOPERATEWIDGET_H
