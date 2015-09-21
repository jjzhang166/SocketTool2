#ifndef UDPSERVERWIDGET_H
#define UDPSERVERWIDGET_H

#include <QWidget>
#include "stdafx.h"

namespace Ui {
class UdpSocketWidget;
}

class UdpSocketWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UdpSocketWidget(QWidget *parent = 0);
    ~UdpSocketWidget();

public slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void udpSocketCreated(QUdpSocket* udpSocket);

private:
    Ui::UdpSocketWidget *ui;
};

#endif // UDPSERVERWIDGET_H
