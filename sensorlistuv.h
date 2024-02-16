#ifndef SENSORLISTUV_H
#define SENSORLISTUV_H

#include "sensorlistobj.h"

class SensorListUV : public SensorListObj
{
private:
    static const QString UVicon;
public:
    SensorListUV(const QString&);
    ~SensorListUV();
};

#endif // SENSORLISTUV_H
