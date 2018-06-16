#ifndef TEMP_HUMI_LIGH_H
#define TEMP_HUMI_LIGH_H

#include "enddevice.h"

class Temp_Humi_Ligh : public Enddevice
{
public:
    explicit Temp_Humi_Ligh();

    void ValueOf(QByteArray&);
    int getTemp();
    int getHumi();
    float getLigh();

private :
    int temperature;
    int humidity;
    float light;

};

#endif // TEMP_HUMI_LIGH_H
