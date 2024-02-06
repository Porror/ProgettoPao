#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Sensor.h"
#include <list>
#include <string>
#include "Observer.h"

class controller
{
private:
    std::string SaveAddress;
    std::list<std::pair<Sensor*,std::list<Observer*>>> sensors;
    void updateName(const std::string&,std::list<Observer*>);
    void updateVal(std::list<Observer*>,Sensor*) const;
    void attach(Observer*,const Sensor*);
    void detach(Observer*,const Sensor*);
public:
    controller();
    ~controller();
    std::string getSaveAddress() const;
    void setSaveAddress(const std::string&);
    void save() const;
    void addSensor(/*TODO Definire tipi di dato utilizzati*/);
    void removeSensor(/*TODO Definire tipi di dato utilizzati*/);
};

#endif // CONTROLLER_H
