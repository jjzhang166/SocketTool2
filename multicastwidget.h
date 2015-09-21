#ifndef MULTICASTWIDGET_H
#define MULTICASTWIDGET_H

#include <QWidget>
#include "stdafx.h"

namespace Ui {
class MulticastWidget;
}

class MulticastWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MulticastWidget(QWidget *parent = 0);
    ~MulticastWidget();

public slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void multicastCreated(QUdpSocket* udpSocket, const QString& multicastAddress);

private:
    Ui::MulticastWidget *ui;
};

#endif // MULTICASTWIDGET_H
