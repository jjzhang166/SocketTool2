#ifndef TCPSERVEROPERATEWIDGET_H
#define TCPSERVEROPERATEWIDGET_H

#include <QWidget>
#include "stdafx.h"

namespace Ui {
class TcpServeroperatewidget;
}

class TcpServeroperatewidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServeroperatewidget(QWidget *parent = 0);
    ~TcpServeroperatewidget();
    void setTcpServer(QTcpServer* tcpServer);

public slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void newConnectionComing();
    void acceptSocketError(QAbstractSocket::SocketError socketError);

private:
    Ui::TcpServeroperatewidget *ui;
    QTcpServer* m_tcpServer;
    QHostAddress m_hostAddress;
    unsigned short m_port;
};

#endif // TCPSERVEROPERATEWIDGET_H
