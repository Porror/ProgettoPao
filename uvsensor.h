#ifndef UVSENSOR_H
#define UVSENSOR_H

#include "Sensor.h"


class UVSensor:public Sensor
{
private:
    static const int minscale=0;
    static const int maxscale=11;
public:
    UVSensor(const std::string&, const modelli& mod=modelli{costante});
    ~UVSensor() override;
    //Dipende dalla posizione geografica e dalle condizioni atmosferiche, nelle nostre zone questa è una scala ragionevole
    void simulate(unsigned int) override;
    void save(Saver*)const override;
};

#endif // UVSENSOR_H
