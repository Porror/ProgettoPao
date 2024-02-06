#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
class Sensor;

class Observer{
public:
    virtual void updateName(const std::string&)=0;
    virtual void updateVal(const Sensor*)=0;
    virtual ~Observer(){};
};

#endif // OBSERVER_H
