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

    void setMin(const double& min)override;
    void setMax(const double& min)override;
    static double getMinscale();

    void save(Saver*)const override;
    //Dipende dalla posizione geografica e dalle condizioni atmosferiche, nelle nostre zone questa è una scala ragionevole
    void simulate(unsigned int) override;

    static double getMinScale();
    static double getMaxscale();
};

#endif // UVSENSOR_H
