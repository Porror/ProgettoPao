#ifndef SENSORLISTWIND_H
#define SENSORLISTWIND_H

#include "sensorlistobj.h"

class SensorListWind : public SensorListObj
{
private:
    static const QString Windicon;
public:
    SensorListWind(const QString&);
};

#endif // SENSORLISTWIND_H
