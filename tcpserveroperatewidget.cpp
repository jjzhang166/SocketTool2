#include "tcpserveroperatewidget.h"
#include "ui_tcpserveroperatewidget.h"

TcpServeroperatewidget::TcpServeroperatewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServeroperatewidget)
{
    ui->setupUi(this);
    m_tcpServer = nullptr;
}

TcpServeroperatewidget::~TcpServeroperatewidget()
{
    if (m_tcpServer != nullptr)
    {
        m_tcpServer->close();
        m_tcpServer->deleteLater();
    }
    delete ui;
}

void TcpServeroperatewidget::setTcpServer(QTcpServer *tcpServer)
{
    Q_ASSERT(m_tcpServer == nullptr);
    if (tcpServer == nullptr)
        return;

    m_tcpServer = tcpServer;
    m_hostAddress = m_tcpServer->serverAddress();
    m_port = m_tcpServer->serverPort();
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(newConnectionComing()));
    connect(m_tcpServer, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(acceptSocketError(QAbstractSocket::SocketError)));
    ui->labelLocalPort->setText(QString(tr("监听端口: %1").arg(m_tcpServer->serverPort())));
    if (m_tcpServer->isListening())
    {
        ui->pushButtonStart->setEnabled(false);
        ui->pushButtonStop->setEnabled(true);
        ui->labelSocketState->setText(tr("已启动"));
    }
    else
    {
        ui->pushButtonStart->setEnabled(true);
        ui->pushButtonStop->setEnabled(false);
        ui->labelSocketState->setText(tr("已停止"));
    }
}

void TcpServeroperatewidget::on_pushButtonStart_clicked()
{
    if (!m_tcpServer->listen(m_hostAddress, m_port))
    {
        QString error = QString("Start TCP Server failed! %1").arg(m_tcpServer->errorString());
        QMessageBox::critical(this, tr("Error"), error);
    }
    if (m_tcpServer->isListening())
    {
        ui->pushButtonStart->setEnabled(false);
        ui->pushButtonStop->setEnabled(true);
        ui->labelSocketState->setText(tr("已启动"));
    }
    else
    {
        ui->pushButtonStart->setEnabled(true);
        ui->pushButtonStop->setEnabled(false);
        ui->labelSocketState->setText(tr("已停止"));
    }
}

void TcpServeroperatewidget::on_pushButtonStop_clicked()
{
    m_tcpServer->close();
    if (m_tcpServer->isListening())
    {
        ui->pushButtonStart->setEnabled(false);
        ui->pushButtonStop->setEnabled(true);
        ui->labelSocketState->setText(tr("已启动"));
    }
    else
    {
        ui->pushButtonStart->setEnabled(true);
        ui->pushButtonStop->setEnabled(false);
        ui->labelSocketState->setText(tr("已停止"));
    }
}

void TcpServeroperatewidget::newConnectionComing()
{
    QTcpSocket* tcpSocket = m_tcpServer->nextPendingConnection();
    if (tcpSocket != nullptr)
    {
        tcpSocket->close();
        tcpSocket->deleteLater();
    }
}

void TcpServeroperatewidget::acceptSocketError(QAbstractSocket::SocketError socketError)
{
    QString msg = QString("%1 发生错误：%4").arg(QTime::currentTime().toString()).
            arg(m_tcpServer->errorString());
    ui->textBrowser->appendPlainText(msg);
}
