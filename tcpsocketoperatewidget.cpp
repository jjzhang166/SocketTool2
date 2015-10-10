#include "tcpsocketoperatewidget.h"
#include "ui_tcpsocketoperatewidget.h"

TcpSocketOperateWidget::TcpSocketOperateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpSocketOperateWidget)
{
    ui->setupUi(this);

    m_peerPort = 0;
    m_socket= nullptr;
}

TcpSocketOperateWidget::~TcpSocketOperateWidget()
{
    if (m_socket != nullptr)
    {
        m_socket->close();
        m_socket->deleteLater();
    }
    delete ui;
}

void TcpSocketOperateWidget::setTcpSocket(QTcpSocket *tcpSocket, const QHostAddress &peerHost, const unsigned short &peerPort)
{
    Q_ASSERT(m_socket == nullptr);
    if (tcpSocket == nullptr)
        return;

    m_socket = tcpSocket;
    m_peerAddress = peerHost;
    m_peerPort = peerPort;

    socketStateChanged(m_socket->state());
    ui->labelPeerAddress->setText(QString(tr("对方地址：%1")).arg(m_peerAddress.toString()));
    ui->labelPeerPort->setText(QString(tr("对方端口：%1")).arg(m_peerPort));
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);
    ui->labelLocalPort->setText(QString(tr("本地端口：%1")).arg(m_socket->localPort()));

    connect(m_socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(soketReadyRead()));
}

void TcpSocketOperateWidget::on_pushButtonConnect_clicked()
{
    m_socket->connectToHost(m_peerAddress, m_peerPort);
    ui->pushButtonConnect->setEnabled(false);
}

void TcpSocketOperateWidget::on_pushButtonDisconnect_clicked()
{
    m_socket->disconnectFromHost();
}

void TcpSocketOperateWidget::socketConnected()
{
    ui->pushButtonConnect->setEnabled(false);
    ui->pushButtonDisconnect->setEnabled(true);
}

void TcpSocketOperateWidget::socketDisconnected()
{
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);
}

void TcpSocketOperateWidget::socketError(QAbstractSocket::SocketError)
{
    QString msg = QString("%1 发生错误：%2").arg(QTime::currentTime().toString()).
            arg(m_socket->errorString());
    ui->textBrowser->appendPlainText(msg);
}

void TcpSocketOperateWidget::socketStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState:
        ui->labelStatus->setText(tr("未连接"));
        ui->pushButtonConnect->setEnabled(true);
        break;

    case QAbstractSocket::HostLookupState:
        ui->labelStatus->setText(tr("主机名查找"));
        break;

    case QAbstractSocket::ConnectingState:
        ui->labelStatus->setText(tr("正在连接"));
        break;

    case QAbstractSocket::ConnectedState:
        ui->labelStatus->setText(tr("已连接"));
        break;

    case QAbstractSocket::BoundState:
        ui->labelStatus->setText(tr("已绑定"));
        break;

    case QAbstractSocket::ListeningState:
        ui->labelStatus->setText(tr("正在监听"));
        break;

    case QAbstractSocket::ClosingState:
        ui->labelStatus->setText(tr("正在关闭"));
        break;

    default:
        break;
    }

    ui->labelLocalPort->setText(QString(tr("本地端口：%1")).arg(m_socket->localPort()));
}

void TcpSocketOperateWidget::soketReadyRead()
{
    if (m_socket != nullptr && m_socket->bytesAvailable() > 0)
    {
        QByteArray data = m_socket->readAll();
        QString msg = QString("%1 收到数据：%2").arg(QTime::currentTime().toString()).
                arg(data.constData());
        ui->textBrowser->appendPlainText(msg);
    }
}

void TcpSocketOperateWidget::on_pushButtonSend_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();
    if (m_socket != nullptr && m_socket->isWritable() && !text.isEmpty())
    {
        QString msg = QString("%1 发送数据：%2").arg(QTime::currentTime().toString()).
                arg(text);
        ui->textBrowser->appendPlainText(msg);
        QByteArray data = text.toUtf8();
        m_socket->write(data);
        ui->plainTextEdit->clear();
    }
}
