#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPushButton *buttonCreateSocket = new QPushButton(tr("CreateSocket"), this);
    QMenu* menuCreateSocket = new QMenu(this);
    QAction* actionTcpServer = new QAction(tr("TCP Server"), this);
    QAction* actionTcpClient = new QAction(tr("TCP Client"), this);
    //QAction* actionUdpServer = new QAction(tr("UDP Server"), this);
    //actionUdpServer->setObjectName(QStringLiteral("actionUdpServer"));
    //QAction* actionUdpClient = new QAction(tr("UDP Client"), this);
    //actionUdpClient->setObjectName(QStringLiteral("actionUdpClient"));
    QAction* actionUdpSocket = new QAction(tr("UDP Socket"), this);
    actionUdpSocket->setObjectName(QStringLiteral("actionUdpSocket"));
    QAction* actionUdpGroup = new QAction(tr("UDP Group"), this);
    actionUdpGroup->setObjectName(QStringLiteral("actionUdpGroup"));

    ui->setupUi(this);

    ui->mainToolBar->insertWidget(ui->actionCreateSocket, buttonCreateSocket);
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
    QWidget *w  = current->data(Qt::UserRole).value<QWidget*>();
    if (w != nullptr)
        ui->stackedWidget->setCurrentWidget(w);
}

void MainWindow::on_actionUdpSocket_triggered()
{
    UdpSocketWidget* w = new UdpSocketWidget(this);
    connect(w, SIGNAL(udpSocketCreated(QUdpSocket*)), this, SLOT(udpSocketCreated(QUdpSocket*)));
    w->show();
}

//void MainWindow::on_actionUdpServer_triggered()
//{
//    UdpServerWidget* w = new UdpServerWidget(this);
//    connect(w, SIGNAL(udpServerCreated(QUdpSocket*)), this, SLOT(udpServerCreated(QUdpSocket*)));
//    w->show();
//}

//void MainWindow::on_actionUdpClient_triggered()
//{
//    ClientWidget* w = new ClientWidget(QAbstractSocket::UdpSocket, this);
//    connect(w, SIGNAL(udpClientCreated(QUdpSocket*, const QString&, const int&)), this, SLOT(udpClientCreated(QUdpSocket*, const QString&, const int&)));
//    w->show();
//}

void MainWindow::on_actionUdpGroup_triggered()
{
    MulticastWidget* w = new MulticastWidget(this);
    connect(w, SIGNAL(multicastCreated(QUdpSocket*, const QString&)), this, SLOT(multicastCreated(QUdpSocket*, const QString&)));
    w->show();
    //w->showNormal();
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
    ui->stackedWidget->setCurrentWidget(w);
}

//void MainWindow::udpServerCreated(QUdpSocket *udpSocket)
//{
//    QString str = QString("[UDP Server]-%1:%2").arg(udpSocket->localAddress().toString()).arg(udpSocket->localPort());
//    SocketOperateWidget *w = new SocketOperateWidget(this);
//    w->setServerSocket(udpSocket);
//    ui->stackedWidget->addWidget(w);
//    QListWidgetItem *item = new QListWidgetItem(str, ui->listWidget);
//    item->setData(Qt::UserRole, QVariant::fromValue(w));
//    ui->listWidget->addItem(item);
//    ui->listWidget->setCurrentItem(item);
//    //ui->stackedWidget->setCurrentWidget(w);
//}

//void MainWindow::udpClientCreated(QUdpSocket* udpSocket, const QString& peerAddress, const int& peerPort)
//{
//    QString str = QString("[UDP Client]-%1:%2").arg(udpSocket->localAddress().toString()).arg(udpSocket->localPort());
//    SocketOperateWidget *w = new SocketOperateWidget(this);
//    w->setClientSocket(udpSocket, peerAddress, peerPort);
//    ui->stackedWidget->addWidget(w);
//    QListWidgetItem *item = new QListWidgetItem(str, ui->listWidget);
//    item->setData(Qt::UserRole, QVariant::fromValue(w));
//    ui->listWidget->addItem(item);
//    ui->listWidget->setCurrentItem(item);
//    //ui->stackedWidget->setCurrentWidget(w);
//}

void MainWindow::multicastCreated(QUdpSocket *udpSocket, const QString &multicastAddress)
{
    QString str = QString("[UDP Group]-%1:%2(%3)").arg(udpSocket->localAddress().toString()).arg(udpSocket->localPort()).arg(multicastAddress);
    SocketOperateWidget *w = new SocketOperateWidget(this);
    w->setMulticastSocket(udpSocket, multicastAddress);
    ui->stackedWidget->addWidget(w);
    QListWidgetItem *item = new QListWidgetItem(str, ui->listWidget);
    item->setData(Qt::UserRole, QVariant::fromValue(w));
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

void MainWindow::soketReadyRead(QAbstractSocket *s)
{
    QUdpSocket *udpSocket = qobject_cast<QUdpSocket*>(s);
    if (udpSocket != nullptr)
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        qDebug() << datagram << sender << senderPort;
    }
}
