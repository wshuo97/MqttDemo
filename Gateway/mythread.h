#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QVariant>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>

class Mythread : public QThread
{
    Q_OBJECT

public:
    explicit Mythread(QTcpSocket *sock = 0);

protected:
    void run();

private:
    QTcpSocket *socket;

private slots:
    void readMsg();

    void sendMsg(QString);
};

#endif // MYTHREAD_H
