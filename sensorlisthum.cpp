#include "sensorlisthum.h"

const QString SensorListHum::Humicon ="../assets/icons/Humicon.png";

SensorListHum::SensorListHum(const QString& str):SensorListObj(str) {
    setIcon(Humicon);
    update();
}

SensorListHum::~SensorListHum(){};
