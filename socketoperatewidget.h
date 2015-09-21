#ifndef SOCKETOPERATEWIDGET_H
#define SOCKETOPERATEWIDGET_H

#include <QWidget>
#include "stdafx.h"

namespace Ui {
class SocketOperateWidget;
}

class SocketOperateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SocketOperateWidget(QWidget *parent = 0);
    ~SocketOperateWidget();
    void setServerSocket(QAbstractSocket* s);
    void setClientSocket(QAbstractSocket* s, const QString& address, const int& port);
    void setMulticastSocket(QAbstractSocket* s,const QString &multicastAddress);

public slots:
    void soketReadyRead();
    void on_pushButtonSend_clicked();

private:
    Ui::SocketOperateWidget *ui;
    QAbstractSocket* socket;
    bool isServer;
    QString peerAddress;
    int peerPort;
};

#endif // SOCKETOPERATEWIDGET_H
