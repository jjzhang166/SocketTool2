#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPushButton *buttonCreateSocket = new QPushButton(tr("CreateSocket"), this);
    QMenu* menuCreateSocket = new QMenu(this);
    QAction* actionTcpServer = new QAction(tr("TCP Server"), this);
    actionTcpServer->setObjectName(QStringLiteral("actionTcpServer"));
    QAction* actionTcpClient = new QAction(tr("TCP Client"), this);
    actionTcpClient->setObjectName(QStringLiteral("actionTcpClient"));
    QAction* actionUdpSocket = new QAction(tr("UDP Socket"), this);
    actionUdpSocket->setObjectName(QStringLiteral("actionUdpSocket"));
    QAction* actionUdpGroup = new QAction(tr("UDP Group"), this);
    actionUdpGroup->setObjectName(QStringLiteral("actionUdpGroup"));

    ui->setupUi(this);

    ui->mainToolBar->insertWidget(ui->actionRemoveSocket, buttonCreateSocket);
    menuCreateSocket->addAction(actionTcpServer);
    menuCreateSocket->addAction(actionTcpClient);
    //menuCreateSocket->addAction(actionUdpServer);
    //menuCreateSocket->addAction(actionUdpClient);
    menuCreateSocket->addAction(actionUdpSocket);
    menuCreateSocket->addAction(actionUdpGroup);
    buttonCreateSocket->setMenu(menuCreateSocket);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem*)
{
    if (current != nullptr)
    {
        QWidget *w = current->data(Qt::UserRole).value<QWidget*>();
        if (w != nullptr)
            ui->stackedWidget->setCurrentWidget(w);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_actionTcpServer_triggered()
{
    TcpServerWidget* w = new TcpServerWidget(this);
    connect(w, SIGNAL(tcpServerCreated(QTcpServer*)), this, SLOT(tcpServerCreated(QTcpServer*)));
    w->show();
}

void MainWindow::on_actionTcpClient_triggered()
{
    TcpSocketWidget* w = new TcpSocketWidget(this);
    connect(w, SIGNAL(tcpSocketCreated(QTcpSocket*, const QHostAddress&, const unsigned short&)), this, SLOT(tcpSocketCreated(QTcpSocket*, const QHostAddress&, const unsigned short&)));
    w->show();
}

void MainWindow::on_actionUdpSocket_triggered()
{
    UdpSocketWidget* w = new UdpSocketWidget(this);
    connect(w, SIGNAL(udpSocketCreated(QUdpSocket*)), this, SLOT(udpSocketCreated(QUdpSocket*)));
    w->show();
}

void MainWindow::on_actionUdpGroup_triggered()
{
    MulticastWidget* w = new MulticastWidget(this);
    connect(w, SIGNAL(multicastCreated(QUdpSocket*, const QString&)), this, SLOT(multicastCreated(QUdpSocket*, const QString&)));
    w->show();
    //w->showNormal();
}

void MainWindow::on_actionRemoveSocket_triggered()
{
    QListWidgetItem *current = ui->listWidget->currentItem();
    if (current != nullptr)
    {
        QWidget *w = current->data(Qt::UserRole).value<QWidget*>();
        if (w != nullptr)
        {
            ui->listWidget->removeItemWidget(current);
            delete current;
            ui->stackedWidget->removeWidget(w);
            w->deleteLater();
        }
    }
}

void MainWindow::tcpServerCreated(QTcpServer *tcpServer)
{
    QString str = QString("[Tcp Server]-%1:%2").arg(tcpServer->serverAddress().toString()).arg(tcpServer->serverPort());
    TcpServeroperatewidget *w = new TcpServeroperatewidget(this);
    w->setTcpServer(tcpServer);
    ui->stackedWidget->addWidget(w);
    QListWidgetItem *item = new QListWidgetItem(str, ui->listWidget);
    item->setData(Qt::UserRole, QVariant::fromValue(w));
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

void MainWindow::tcpSocketCreated(QTcpSocket *tcpSocket, const QHostAddress& peerHost, const unsigned short& port)
{
    QString str = QString("[Tcp Client]-%1:%2").arg(peerHost.toString()).arg(port);
    TcpSocketOperateWidget *w = new TcpSocketOperateWidget(this);
    w->setTcpSocket(tcpSocket, peerHost, port);
    ui->stackedWidget->addWidget(w);
    QListWidgetItem *item = new QListWidgetItem(str, ui->listWidget);
    item->setData(Qt::UserRole, QVariant::fromValue(w));
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

void MainWindow::udpSocketCreated(QUdpSocket *udpSocket)
{
    QString str = QString("[UDP Socket]-%1:%2").arg(udpSocket->localAddress().toString()).arg(udpSocket->localPort());
    UpdSocketOperateWidget *w = new UpdSocketOperateWidget(this);
    w->setUdpSocket(udpSocket);
    ui->stackedWidget->addWidget(w);
    QListWidgetItem *item = new QListWidgetItem(str, ui->listWidget);
    item->setData(Qt::UserRole, QVariant::fromValue(w));
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

void MainWindow::multicastCreated(QUdpSocket *udpSocket, const QString &multicastAddress)
{
    QString str = QString("[UDP Group]-%1:%2(%3)").arg(udpSocket->localAddress().toString()).arg(udpSocket->localPort()).arg(multicastAddress);
    UpdSocketOperateWidget *w = new UpdSocketOperateWidget(this);
    w->setMulticastSocket(udpSocket, multicastAddress);
    ui->stackedWidget->addWidget(w);
    QListWidgetItem *item = new QListWidgetItem(str, ui->listWidget);
    item->setData(Qt::UserRole, QVariant::fromValue(w));
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

