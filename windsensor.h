#ifndef WINDSENSOR_H
#define WINDSENSOR_H

#include "Sensor.h"

class WindSensor: public Sensor
{
    friend class ConcreteSaver;
private:
    static const int minscale=0;
    static const int maxscale=100;
    std::vector<unsigned int> directions;
    static unsigned int maxangle;
    static unsigned int minangle;
public:
    WindSensor(const std::string&,const modelli& mod=modelli{costante});
    ~WindSensor() override;
    void simulate(unsigned int)override;
    std::vector<unsigned> getWindDirections() const;
    void save(Saver*) const override;
    void setMin(const double& min) override;
    void setMax(const double& min) override;

    static double getMinscale();
    static double getMaxscale();
};
#endif // WINDSENSOR_H
