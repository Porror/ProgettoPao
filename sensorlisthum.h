#ifndef SENSORLISTHUM_H
#define SENSORLISTHUM_H

#include "sensorlistobj.h"

class SensorListHum : public SensorListObj
{
private:
    static const QString Humicon;
public:
    SensorListHum(const QString&);
    ~SensorListHum();
};

#endif // SENSORLISTHUM_H
