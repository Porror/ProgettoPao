#include "sensorlistwind.h"

const QString SensorListWind::Windicon="../assets/icons/Windicon.png";

SensorListWind::SensorListWind(const QString& str):SensorListObj(str){
    setIcon(Windicon);
    update();
}
