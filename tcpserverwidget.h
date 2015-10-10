#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H

#include <QWidget>
#include "stdafx.h"

namespace Ui {
class TcpServerWidget;
}

class TcpServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServerWidget(QWidget *parent = 0);
    ~TcpServerWidget();

public slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void tcpServerCreated(QTcpServer* tcpServer);

private:
    Ui::TcpServerWidget *ui;
};

#endif // TCPSERVERWIDGET_H
