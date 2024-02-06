#ifndef SAVER_H
#define SAVER_H

#include<QJsonObject>

class UVSensor;
class HumiditySensor;
class WindSensor;

class Saver{
private:
    virtual void saveUVSensor(const UVSensor&)=0;
    virtual void saveHumiditysensor(const HumiditySensor&)=0;
    virtual void saveWindSensor(const WindSensor&)=0;

    //dichiarazioni di amicizia
    friend class HumiditySensor;
    friend class UVSensor;
    friend class WindSensor;
};

#endif // SAVER_H
