#include "temp_humi_ligh.h"

Temp_Humi_Ligh::Temp_Humi_Ligh() : temperature(0), humidity(0), light(0)
{
}

void Temp_Humi_Ligh::ValueOf(QByteArray &msg)
{
    unsigned char XH = msg[5], XL = msg[6];
    unsigned char YH = msg[7], YL = msg[8];
    unsigned char GH = msg[9], GL = msg[10];

    temperature = XH*256 + XL;
    humidity    = YH*256 + YL;
    light       = 1.0*(GH*256 + GL)*3012.9/(32768*4);
}

int Temp_Humi_Ligh::getTemp()
{
    return this->temperature;
}

int Temp_Humi_Ligh::getHumi()
{
    return this->humidity;
}

float Temp_Humi_Ligh::getLigh()
{
    return this->light;
}
