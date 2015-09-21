#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QAbstractSocket::SocketType type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    socketType = type;
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_ShowModal);
    setWindowFlags(Qt::Tool);

    ui->lineEditPeerAddress->setText("127.0.0.1");
    QIntValidator* portValidator = new QIntValidator(1, 65535, this);
    ui->lineEditPort->setValidator(portValidator);
    ui->lineEditPort->setText("10000");
    ui->lineEditPeerPort->setText("60000");
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButtonOk_clicked()
{
    int port = ui->lineEditPort->text().toInt();
    if (ui->lineEditPort->text().isEmpty() || port <= 0)
        return;

    int peerPort = ui->lineEditPeerPort->text().toInt();
    if (ui->lineEditPeerPort->text().isEmpty() || peerPort <= 0)
        return;

    QString peerHostAddress = ui->lineEditPeerAddress->text();
    if (peerHostAddress.isEmpty())
        return;

    QObject *p = parent();
    if (p != nullptr)
    {
        if (socketType == QAbstractSocket::UdpSocket)
        {
            QUdpSocket* udpSocket = new QUdpSocket(p);
            if (udpSocket->bind(QHostAddress::Any, port))
            {
                emit udpClientCreated(udpSocket, peerHostAddress, peerPort);
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
}

void ClientWidget::on_pushButtonCancel_clicked()
{
     close();
}
