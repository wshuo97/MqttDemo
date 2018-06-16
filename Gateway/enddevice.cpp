#include "enddevice.h"

Enddevice::Enddevice(QObject *parent) :
    QObject(parent),
    status(0)
{
}

void Enddevice::setStatus(int status)
{
    this->status = status;
}

int Enddevice::getStatus()
{
    return this->status;
}
