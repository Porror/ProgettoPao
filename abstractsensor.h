#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include<vector>
#include<string>

class AbstractSensor
{
public:
    virtual std::string getName() const =0;
    virtual std::vector<double> getVal() const =0;
    virtual double getMax() const=0;
    virtual double getMin() const=0;

    virtual void simula(unsigned int) =0;
    virtual void reset() =0;

    virtual void setName(std::string) =0;

    AbstractSensor(std::string="");
    virtual ~AbstractSensor();
};
#endif // ABSTRACTSENSOR_H
