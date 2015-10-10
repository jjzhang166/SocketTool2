#include "tcpsocketwidget.h"
#include "ui_tcpsocketwidget.h"

TcpSocketWidget::TcpSocketWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpSocketWidget)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_ShowModal);
    setWindowFlags(Qt::Tool);

    ui->lineEditPeerAddress->setText("127.0.0.1");

    QIntValidator* portValidator = new QIntValidator(1, 65535, this);
    ui->lineEditPort->setValidator(portValidator);
    ui->lineEditPort->setText("60000");
}

TcpSocketWidget::~TcpSocketWidget()
{
    delete ui;
}

void TcpSocketWidget::on_pushButtonOk_clicked()
{
    int port = ui->lineEditPort->text().toInt();
    if (ui->lineEditPort->text().isEmpty() || port <= 0)
        return;

    QString hostAddress = ui->lineEditPeerAddress->text();
    if (hostAddress.isEmpty())
        return;

    QHostAddress host(hostAddress);
    if (host.isNull())
        return;

    QObject *p = parent();
    if (p != nullptr)
    {
        QTcpSocket* tcpSocket = new QTcpSocket(p);
        if (tcpSocket != nullptr)
        {
            emit tcpSocketCreated(tcpSocket, host, port);
            close();
        }
    }
}

void TcpSocketWidget::on_pushButtonCancel_clicked()
{
    close();
}
