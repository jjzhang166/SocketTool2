#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"

TcpServerWidget::TcpServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServerWidget)
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

TcpServerWidget::~TcpServerWidget()
{
    delete ui;
}

void TcpServerWidget::on_pushButtonOk_clicked()
{
    int port = ui->lineEditPort->text().toInt();
    if (ui->lineEditPort->text().isEmpty() || port <= 0)
        return;

    QString hostAddress = ui->comboBox->currentData().toString();
    QObject *p = parent();
    if (p != nullptr)
    {
        QTcpServer* tcpServer = new QTcpServer(p);
        if (tcpServer->listen(hostAddress.isEmpty() ? QHostAddress::Any : QHostAddress(hostAddress), port))
        {
            emit tcpServerCreated(tcpServer);
            close();
        }
        else
        {
            QString error = QString("Create TCP Server failed! %1").arg(tcpServer->errorString());
            QMessageBox::critical(this, tr("Error"), error);
            tcpServer->deleteLater();
        }
    }
}

void TcpServerWidget::on_pushButtonCancel_clicked()
{
    close();
}
