#include "mythread.h"

Mythread::Mythread(QTcpSocket *sock)
{
    socket=sock;
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMsg()));
}

void Mythread::run()
{
    qDebug()<<socket->isOpen()<<endl;
}

void Mythread::readMsg()
{
    QByteArray qdb=socket->readAll();
    QString msg=QVariant(qdb).toString();
    qDebug()<<msg<<" is the sent msg!"<<endl;
    emit sendMsg(msg);
}

void Mythread::sendMsg(QString msg)
{
    socket->write(msg.toAscii());
    socket->flush();
}
