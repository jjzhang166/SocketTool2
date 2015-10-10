#ifndef TCPSOCKETWIDGET_H
#define TCPSOCKETWIDGET_H

#include <QWidget>
#include "stdafx.h"

namespace Ui {
class TcpSocketWidget;
}

class TcpSocketWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpSocketWidget(QWidget *parent = 0);
    ~TcpSocketWidget();

public slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void tcpSocketCreated(QTcpSocket* tcpSocket, const QHostAddress& peerHost, const unsigned short& peerPort);

private:
    Ui::TcpSocketWidget *ui;
};

#endif // TCPSOCKETWIDGET_H
