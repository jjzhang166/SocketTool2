#include "socketoperatewidget.h"
#include "ui_socketoperatewidget.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


SocketOperateWidget::SocketOperateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SocketOperateWidget)
{
    ui->setupUi(this);

    socket = nullptr;
    isServer = false;
}

SocketOperateWidget::~SocketOperateWidget()
{
    delete ui;
}

void SocketOperateWidget::setServerSocket(QAbstractSocket *s)
{
    Q_ASSERT(socket == nullptr);
    if (s == nullptr)
        return;

    socket = s;
    isServer = true;
    connect(socket, SIGNAL(readyRead()), this, SLOT(soketReadyRead()));
    if (socket->socketType() == QAbstractSocket::UdpSocket)
    {
        ui->labelSocketState->hide();
        if (isServer)
        {
            ui->labelPeerAddress->hide();
            ui->labelPeerPort->hide();
        }
        QString tmp = QString("本地端口: %1").arg(socket->localPort());
        ui->labelLocalPort->setText(tmp);
        ui->pushButtonStart->hide();
        ui->pushButtonStop->hide();
        ui->pushButtonConnect->hide();
        ui->pushButtonDisconnect->hide();
    }
}

void SocketOperateWidget::setClientSocket(QAbstractSocket *s, const QString &address, const int &port)
{
    Q_ASSERT(socket == nullptr);
    if (s == nullptr)
        return;

    socket = s;
    isServer = false;
    peerAddress = address;
    peerPort = port;
    connect(socket, SIGNAL(readyRead()), this, SLOT(soketReadyRead()));
    if (socket->socketType() == QAbstractSocket::UdpSocket)
    {
        ui->labelSocketState->hide();
        QString tmp;
        if (!isServer)
        {
            tmp = QString("对方地址: %1").arg(peerAddress);
            ui->labelPeerAddress->setText(tmp);
            tmp = QString("对方端口: %1").arg(QString::number(peerPort));
            ui->labelPeerPort->setText(tmp);
        }
        tmp = QString("本地端口: %1").arg(socket->localPort());
        ui->labelLocalPort->setText(tmp);
        ui->pushButtonStart->hide();
        ui->pushButtonStop->hide();
        ui->pushButtonConnect->hide();
        ui->pushButtonDisconnect->hide();
    }
}

void SocketOperateWidget::setMulticastSocket(QAbstractSocket *s, const QString &multicastAddress)
{
    Q_ASSERT(socket == nullptr);
    if (s == nullptr)
        return;

    socket = s;
    isServer = false;
    peerAddress = "";
    peerPort = 0;

    ui->labelSocketState->hide();
    QString tmp;
    if (!isServer)
    {
        tmp = QString("组播地址: %1").arg(multicastAddress);
        ui->labelPeerAddress->setText(tmp);
        tmp = QString("组播端口: %1").arg(s->localPort());
        ui->labelPeerPort->setText(tmp);
    }
    ui->labelLocalPort->hide();
    ui->pushButtonStart->hide();
    ui->pushButtonStop->hide();
    ui->pushButtonConnect->hide();
    ui->pushButtonDisconnect->hide();
}

void SocketOperateWidget::soketReadyRead()
{
    if (socket != nullptr)
    {
        if (socket->socketType() == QAbstractSocket::UdpSocket)
        {
            QUdpSocket *udpSocket = qobject_cast<QUdpSocket*>(socket);
            if (udpSocket != nullptr)
            {
                QByteArray datagram;
                datagram.resize(udpSocket->pendingDatagramSize());
                QHostAddress sender;
                quint16 senderPort;
                udpSocket->readDatagram(datagram.data(), datagram.size(),
                                        &sender, &senderPort);

                QString msg = QString("%1 [%2:%3] 收到数据：%4").arg(QTime::currentTime().toString()).
                        arg(sender.toString()).arg(senderPort).arg(datagram.constData());
                ui->textBrowser->appendPlainText(msg);

                if (isServer)
                {
                    // 回复
                    msg = QString("%1 回复数据：%2").arg(QTime::currentTime().toString()).arg(datagram.constData());
                    ui->textBrowser->appendPlainText(msg);
                    udpSocket->writeDatagram(datagram, sender, senderPort);
                }
            }
        }
    }
}

void SocketOperateWidget::on_pushButtonSend_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();
    if (!isServer && socket != nullptr && !text.isEmpty())
    {
        if (socket->socketType() == QAbstractSocket::UdpSocket)
        {
            QUdpSocket *udpSocket = qobject_cast<QUdpSocket*>(socket);
            if (udpSocket != nullptr)
            {
                QString msg = QString("%1 发送数据：%2").arg(QTime::currentTime().toString()).arg(text);
                ui->textBrowser->appendPlainText(msg);
                QByteArray datagram = text.toLatin1();
                //char c = 0x2;
                //udpSocket->writeDatagram(&c, 1, QHostAddress(peerAddress), peerPort);
                udpSocket->writeDatagram(datagram, QHostAddress(peerAddress), peerPort);
                qDebug() << peerAddress << peerPort;
                ui->plainTextEdit->clear();
            }
        }
    }
}
