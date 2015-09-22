#ifndef UPDSOCKETOPERATEWIDGET_H
#define UPDSOCKETOPERATEWIDGET_H

#include <QWidget>
#include "stdafx.h"

namespace Ui {
class UpdSocketOperateWidget;
}

class UpdSocketOperateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UpdSocketOperateWidget(QWidget *parent = 0);
    ~UpdSocketOperateWidget();
    void setUdpSocket(QUdpSocket* s);
    void setMulticastSocket(QUdpSocket* s, const QString &multicastAddress);

public slots:
    void socketError(QAbstractSocket::SocketError);
    void soketReadyRead();
    void on_pushButtonSend_clicked();

private:
    Ui::UpdSocketOperateWidget *ui;
    QUdpSocket* m_socket;
    bool m_isMulticast;
    QHostAddress m_multicastAddress;
};

#endif // UPDSOCKETOPERATEWIDGET_H
