#ifndef SERIALSERVICE_H
#define SERIALSERVICE_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QTimer>

#include "posix_qextserialport.h"
#define READTIME 100

class SerialService : public QObject
{
    Q_OBJECT
public:
    explicit SerialService(QObject *parent = 0);
    int writeToSerial(const QByteArray &byte);
    bool openCom();
    bool closeCom();
    void releaseSerial();
    QTimer* getTimer();
    int getComState();
signals:
    void receiveMsgFromSerial(QByteArray);
public slots:
    void readFromSerial();
private:
    Posix_QextSerialPort *my_com;
    int com_state;
    QTimer *read_timer;
};

#endif // SERIALSERVICE_H
