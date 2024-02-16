#include "sensorlistuv.h"

const QString SensorListUV::UVicon ="../assets/icons/UVicon.png";

SensorListUV::SensorListUV(const QString& str):SensorListObj(str){
    setIcon(UVicon);
    update();
}

SensorListUV::~SensorListUV(){}
