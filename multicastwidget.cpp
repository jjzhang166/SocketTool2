#include "multicastwidget.h"
#include "ui_multicastwidget.h"
#include "stdafx.h"

MulticastWidget::MulticastWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MulticastWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_ShowModal);
    setWindowFlags(Qt::Tool);

    QIntValidator* portValidator = new QIntValidator(1, 65535, this);
    ui->lineEditPort->setValidator(portValidator);
    ui->lineEditPort->setText("60000");

    ui->comboBox->addItem(tr("AnyIPv4-address"), "");
    QList<QHostAddress>	hostAddressList = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, hostAddressList)
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
            ui->comboBox->addItem(address.toString(), address.toString());
    }

    ui->lineEditcMulticastAddress->setText("224.0.0.0");
}

MulticastWidget::~MulticastWidget()
{
    delete ui;
}

void MulticastWidget::on_pushButtonOk_clicked()
{
    if (ui->lineEditcMulticastAddress->text().isEmpty())
        return;

    if (ui->lineEditcMulticastAddress->text().isEmpty())
        return;

    int port = ui->lineEditPort->text().toInt();
    if (ui->lineEditPort->text().isEmpty() || port <= 0)
        return;

    QString hostAddress = ui->comboBox->currentData().toString();
    QString multicastAddress = ui->lineEditcMulticastAddress->text();

    QObject *p = parent();
    if (p != nullptr)
    {
        QUdpSocket* udpSocket = new QUdpSocket(p);
        if (udpSocket->bind(hostAddress.isEmpty() ? QHostAddress::AnyIPv4 : QHostAddress(hostAddress), port))
        {
            udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0); // 禁止本机接收
            if (udpSocket->joinMulticastGroup(QHostAddress(multicastAddress)))
            {
                emit multicastCreated(udpSocket, multicastAddress);
                close();
            }
            else
            {
                QString error = QString("join multicast group failed! %1").arg(udpSocket->errorString());
                QMessageBox::critical(this, tr("Error"), error);
                udpSocket->deleteLater();
            }
        }
        else
        {            
            QString error = QString("Create socket failed! %1").arg(udpSocket->errorString());
            QMessageBox::critical(this, tr("Error"), error);
            udpSocket->deleteLater();
        }
    }
}

void MulticastWidget::on_pushButtonCancel_clicked()
{
    close();
}
