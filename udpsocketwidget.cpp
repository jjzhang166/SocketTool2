#include "udpsocketwidget.h"
#include "ui_udpsocketwidget.h"
#include "stdafx.h"

UdpSocketWidget::UdpSocketWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UdpSocketWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_ShowModal);
    setWindowFlags(Qt::Tool);

    QIntValidator* portValidator = new QIntValidator(1, 65535, this);
    ui->lineEditPort->setValidator(portValidator);
    ui->lineEditPort->setText("60000");

    ui->comboBox->addItem(tr("Any-address"), "");
    QList<QHostAddress>	hostAddressList = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, hostAddressList)
    {
       ui->comboBox->addItem(address.toString(), address.toString());
    }
}

UdpSocketWidget::~UdpSocketWidget()
{
    delete ui;
}

void UdpSocketWidget::on_pushButtonOk_clicked()
{
    int port = ui->lineEditPort->text().toInt();
    if (ui->lineEditPort->text().isEmpty() || port <= 0)
        return;

    QString hostAddress = ui->comboBox->currentData().toString();
    QObject *p = parent();
    if (p != nullptr)
    {
        QUdpSocket* udpSocket = new QUdpSocket(p);
        if (udpSocket->bind(hostAddress.isEmpty() ? QHostAddress::Any : QHostAddress(hostAddress), port))
        {
            emit udpSocketCreated(udpSocket);
            close();
        }
        else
        {
            QString error = QString("Create socket failed! %1").arg(udpSocket->errorString());
            QMessageBox::critical(this, tr("Error"), error);
            udpSocket->deleteLater();
        }
    }
}

void UdpSocketWidget::on_pushButtonCancel_clicked()
{
    close();
}
