#ifndef ENDDEVICE_H
#define ENDDEVICE_H

#include <QObject>

class Enddevice : public QObject
{
    Q_OBJECT
public:
    explicit Enddevice(QObject *parent = 0);
    
    void setStatus(int);

    int getStatus();

signals:
    
public slots:
    
private :
    int status;
};

#endif // ENDDEVICE_H
