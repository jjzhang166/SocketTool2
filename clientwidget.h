#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include "stdafx.h"

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QAbstractSocket::SocketType type, QWidget *parent = 0);
    ~ClientWidget();

public slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void udpClientCreated(QUdpSocket* udpSocket, const QString& peerAddress, const int& peerPort);

private:
    Ui::ClientWidget *ui;
    QAbstractSocket::SocketType socketType;
};

#endif // CLIENTWIDGET_H
