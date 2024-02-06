#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H

#include "Sensor.h"

class HumiditySensor: public Sensor
{
private:
    static const int minscale=0;
    static const int maxscale=100;
public:
    HumiditySensor(const std::string&, const modelli& mod=modelli{costante});
    ~HumiditySensor()override;
    void simulate(unsigned int) override;
    void save(Saver*)const override;
    void setMin(const double& min) override;
    void setMax(const double& min) override;
};

#endif // HUMIDITYSENSOR_H
