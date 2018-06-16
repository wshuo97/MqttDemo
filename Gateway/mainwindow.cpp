#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUI();

    UpLoad=0;

    sensormsg="Initing\n";

    timer=new QTimer(this);
    serial_control = new SerialService();
    sensor = new Temp_Humi_Ligh();

    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("127.0.0.1"), 8888);

    thread=new Mythread(socket);

    connect(this->serial_control, SIGNAL(receiveMsgFromSerial(QByteArray)), this, SLOT(handleMSG(QByteArray)));
    connect(this, SIGNAL(goMsg(QString)), this, SLOT(upMsg(QString)));
    connect(this,SIGNAL(sendTo(QString)),this->thread,SLOT(sendMsg(QString)));
    connect(this->socket, SIGNAL(connected()), this, SLOT(setUpload()));
    connect(this->timer,SIGNAL(timeout()),this,SLOT(handleTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{
    ui->lcd_t->setNumDigits(8);
    ui->lcd_t->setPalette(Qt::black);
    ui->lcd_h->setNumDigits(8);
    ui->lcd_h->setPalette(Qt::black);
    ui->lcd_l->setNumDigits(8);
    ui->lcd_l->setPalette(Qt::black);
}

void MainWindow::handleMSG(QByteArray msg)
{
    if(msg.length() < 6)
        return ;

    //温度传感器
    if(0x02 == msg[3] && 0x01 == msg[4])
    {
        QString str = "";
        sensor->ValueOf(msg);
        upLcd_display(sensor);
    }
}

void MainWindow::upLcd_display(Temp_Humi_Ligh * tmp)
{
    ui->lcd_t->display(tmp->getTemp());
    ui->lcd_h->display(tmp->getHumi());
    ui->lcd_l->display(tmp->getLigh());
    QString t=QString::number(tmp->getTemp(),10);
    QString h=QString::number(tmp->getHumi(),10);
    QString l=QString("%1").arg(tmp->getLigh());
    sensormsg=t+":"+h+":"+l+"\n\r";
}

void MainWindow::on_button_clicked()
{
    if(serial_control->getComState()) closeSerial();
    else openSerial();
}

void MainWindow::openSerial()
{
    if(serial_control->openCom())
    {
        ui->button->setText("OFF");
        ui->button->setStyleSheet(PINK);
        thread->start();
        UpLoad=1;
        timer->start(2000);
    }
    else
    {
        UpLoad=0;
    }
}

void MainWindow::closeSerial()
{
    serial_control->closeCom();
}

void MainWindow::setUpload()
{
    UpLoad=1;
}

void MainWindow::upMsg(QString mesg)
{
    ui->msgInfo->append(mesg);
    if(UpLoad == 1)
    {
        emit sendTo(mesg);
    }
}

void MainWindow::handleTime()
{
    emit goMsg(sensormsg);
}
