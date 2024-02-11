#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <vector>
#include "Saver.h"

enum modelli{normale,uniforme,costante};

class Sensor{
    friend class ConcreteSaver;
private:
    std::string name;

protected:
    modelli simulationType;
    std::vector<double> data;
    //Valori di minimo e massimo per la simulazione
    double min;
    double max;
public:
    void setName(const std::string&);
    //indicano i valori massimi e minimi generabili dalla simulazione
    virtual void setMin(const double&);
    virtual void setMax(const double&);
    double getMin() const;
    double getMax() const;
    std::string getName() const;
    virtual void setSimulationType(const modelli&);
    modelli getSimulator() const;
    virtual void save(Saver *) const =0;
    double getMinsim() const;
    double getMaxsim() const;
    virtual void simulate(unsigned int);
    std::vector<double> getData() const;
    Sensor(const std::string&,const modelli& mod=modelli{costante});
    //nella distruzione non devo eliminare la lista di observer in quanto non necessario
    virtual ~Sensor();
};
#endif // SENSOR_H
