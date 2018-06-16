#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMutex>
#include <QTimer>
#include <QFile>
#include <QThread>
#include <QString>

#include "posix_qextserialport.h"
#include "temp_humi_ligh.h"
#include "qextserialbase.h"
#include "serialservice.h"
#include "enddevice.h"
#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

private:
    SerialService *serial_control;
    QTcpSocket *socket;
    Temp_Humi_Ligh *sensor;
    Mythread *thread;
    QTimer *timer;

    QString sensormsg;

    int UpLoad;

private:
    void InitUI();

    void openSerial(void);

    void closeSerial(void);

    void upLcd_display(Temp_Humi_Ligh*);

private slots:
    void handleMSG(QByteArray);

    void on_button_clicked();

    void setUpload();

    void upMsg(QString);

    void handleTime();

signals:
    void goMsg(QString);

    void sendTo(QString);
};

const QString BLUE  = "QPushButton{background:blue}";
const QString GREEN = "QPushButton{background:green}";
const QString RED   = "QPushButton{background:red}";
const QString PINK  = "QPushButton{background:pink}";
const QString BROWN = "QPushButton{background:borwn}";
const QString YELLOW= "QPushButton{background:yellow}";
const QString WHITE = "QPushButton{background:white}";

#endif // MAINWINDOW_H
