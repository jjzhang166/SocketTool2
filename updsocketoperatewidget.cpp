#include "updsocketoperatewidget.h"
#include "ui_updsocketoperatewidget.h"

UpdSocketOperateWidget::UpdSocketOperateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdSocketOperateWidget)
{
    ui->setupUi(this);
    socket = nullptr;

    ui->lineEditPeerAddress->setText("127.0.0.1");
    QIntValidator* portValidator = new QIntValidator(1, 65535, this);
    ui->lineEditPeerPort->setValidator(portValidator);
    ui->lineEditPeerPort->setText("60000");
}

UpdSocketOperateWidget::~UpdSocketOperateWidget()
{
    delete ui;
}

void UpdSocketOperateWidget::setUdpSocket(QUdpSocket *s)
{
    Q_ASSERT(socket == nullptr);
    if (s == nullptr)
        return;

    socket = s;
    connect(socket, SIGNAL(readyRead()), this, SLOT(soketReadyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    QString tmp = QString("本地端口: %1").arg(socket->localPort());
    ui->labelLocalPort->setText(tmp);
}

void UpdSocketOperateWidget::socketError(QAbstractSocket::SocketError)
{
    QString msg = QString("%1 发生错误：%2").arg(QTime::currentTime().toString()).
            arg(socket->errorString());
    ui->textBrowser->appendPlainText(msg);
}

void UpdSocketOperateWidget::soketReadyRead()
{
    if (socket != nullptr)
    {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(datagram.data(), datagram.size(),
                             &sender, &senderPort);

        QString msg = QString("%1 从[%2:%3] 收到数据：%4").arg(QTime::currentTime().toString()).
                arg(sender.toString()).arg(senderPort).arg(datagram.constData());
        ui->textBrowser->appendPlainText(msg);
    }
}

void UpdSocketOperateWidget::on_pushButtonSend_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();
    QString peerAddress = ui->lineEditPeerAddress->text();
    int peerPort = ui->lineEditPeerPort->text().toInt();
    if (socket != nullptr && !text.isEmpty() && !peerAddress.isEmpty() && peerPort != 0)
    {
        QString msg = QString("%1 向[%2:%3] 发送数据：%4").arg(QTime::currentTime().toString()).
                arg(peerAddress).arg(peerPort).arg(text);
        ui->textBrowser->appendPlainText(msg);
        QByteArray datagram = text.toLatin1();
        //char c = 0x2;
        //udpSocket->writeDatagram(&c, 1, QHostAddress(peerAddress), peerPort);
        socket->writeDatagram(datagram, QHostAddress(peerAddress), peerPort);
        ui->plainTextEdit->clear();
    }
}
