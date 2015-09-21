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
    void socketError(QAbstractSocket::SocketError);

public slots:
    void soketReadyRead();
    void on_pushButtonSend_clicked();

private:
    Ui::UpdSocketOperateWidget *ui;
    QUdpSocket* socket;
};

#endif // UPDSOCKETOPERATEWIDGET_H
