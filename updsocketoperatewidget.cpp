#include "updsocketoperatewidget.h"
#include "ui_updsocketoperatewidget.h"

UpdSocketOperateWidget::UpdSocketOperateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdSocketOperateWidget)
{
    ui->setupUi(this);
    m_socket = nullptr;
    m_isMulticast = false;

    ui->lineEditPeerAddress->setText("127.0.0.1");
    QIntValidator* portValidator = new QIntValidator(1, 65535, this);
    ui->lineEditPeerPort->setValidator(portValidator);
    ui->lineEditPeerPort->setText("60000");
}

UpdSocketOperateWidget::~UpdSocketOperateWidget()
{
    if (m_socket != nullptr)
    {
        m_socket->close();
        m_socket->deleteLater();
    }
    delete ui;
}

void UpdSocketOperateWidget::setUdpSocket(QUdpSocket *s)
{
    Q_ASSERT(m_socket == nullptr);
    if (s == nullptr)
        return;

    m_socket = s;
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(soketReadyRead()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    ui->labelMulticastAddress->hide();
    QString tmp = QString("本地端口: %1").arg(m_socket->localPort());
    ui->labelLocalPort->setText(tmp);
}

void UpdSocketOperateWidget::setMulticastSocket(QUdpSocket *s, const QString &multicastAddress)
{
    Q_ASSERT(m_socket == nullptr);
    if (s == nullptr)
        return;

    m_socket = s;
    m_multicastAddress = multicastAddress;
    m_isMulticast = true;
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(soketReadyRead()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    QString tmp = QString("组播地址: %1").arg(multicastAddress);
    ui->labelMulticastAddress->setText(tmp);
    tmp = QString("组播端口: %1").arg(m_socket->localPort());
    ui->labelLocalPort->setText(tmp);
    ui->labelPeerAddress->hide();
    ui->lineEditPeerAddress->hide();
    ui->labelPeerPort->hide();
    ui->lineEditPeerPort->hide();
}

void UpdSocketOperateWidget::socketError(QAbstractSocket::SocketError)
{
    QString msg = QString("%1 发生错误：%2").arg(QTime::currentTime().toString()).
            arg(m_socket->errorString());
    ui->textBrowser->appendPlainText(msg);
}

void UpdSocketOperateWidget::soketReadyRead()
{
    if (m_socket != nullptr)
    {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        m_socket->readDatagram(datagram.data(), datagram.size(),
                             &sender, &senderPort);

        QString msg = QString("%1 从[%2:%3] 收到数据：%4").arg(QTime::currentTime().toString()).
                arg(sender.toString()).arg(senderPort).arg(datagram.constData());
        ui->textBrowser->appendPlainText(msg);
    }
}

void UpdSocketOperateWidget::on_pushButtonSend_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();
    if (m_socket != nullptr && !text.isEmpty())
    {
        if (m_isMulticast)
        {
            // 组播
            QString msg = QString("%1 向[%2:%3] 发送数据：%4").arg(QTime::currentTime().toString()).
                    arg(m_multicastAddress.toString()).arg(m_socket->localPort()).arg(text);
            ui->textBrowser->appendPlainText(msg);
            QByteArray datagram = text.toUtf8();
            m_socket->writeDatagram(datagram, m_multicastAddress, m_socket->localPort());
            ui->plainTextEdit->clear();
        }
        else
        {
            QString peerAddress = ui->lineEditPeerAddress->text();
            int peerPort = ui->lineEditPeerPort->text().toInt();
            if (!peerAddress.isEmpty() && peerPort != 0)
            {
                QString msg = QString("%1 向[%2:%3] 发送数据：%4").arg(QTime::currentTime().toString()).
                        arg(peerAddress).arg(peerPort).arg(text);
                ui->textBrowser->appendPlainText(msg);
                QByteArray datagram = text.toUtf8();
                //char c = 0x2;
                //udpSocket->writeDatagram(&c, 1, QHostAddress(peerAddress), peerPort);
                m_socket->writeDatagram(datagram, QHostAddress(peerAddress), peerPort);
                ui->plainTextEdit->clear();
            }
        }
    }
}
