#include"Sensor.h"
#include "error.h"
#include "random"

void Sensor::setName(const std::string& nome){
    name=nome;
}

void Sensor::setMin(const double& m){
    min=m;
}

void Sensor::setMax(const double& m){
    max=m;
}

double Sensor::getMin()const{
    return min;
}

double Sensor::getMax()const{
    return max;
}

std::string Sensor::getName() const{
    return name;
}

void Sensor::setSimulationType(const modelli& model){
    simulationType=model;
}

modelli Sensor::getSimulator() const{
    return simulationType;
}

double Sensor::getMinsim() const{
    if(data.empty()) throw Error(0);

    double ret=data[0];
    for(std::vector<double>::const_iterator it=data.begin()+1;it!=data.end();++it){
        if(*it<ret) ret=*it;
    }
    return ret;
}

double Sensor::getMaxsim() const{
    if(data.empty()) throw Error(0);

    double ret=data[0];
    for(std::vector<double>::const_iterator it=data.begin()+1;it!=data.end();++it){
        if(*it>ret) ret=*it;
    }
    return ret;
}

void Sensor::simulate(unsigned int it){
    if(!data.empty()) data.clear();

    if(min>max) throw Error(1);

    std::random_device rd;
    std::mt19937 gen(rd());

    if(simulationType==modelli{normale})
    {
        double mean=(max+min)/2;
        double stddev=(max-min)/6;
        std::normal_distribution<double> distribution(mean,stddev);
        for(unsigned int i=0;i<it;++i) data.push_back(distribution(gen));
        return;
    }
    if(simulationType==modelli{uniforme}){
        std::uniform_real_distribution<double> distribution(min,max);
        for(unsigned int i=0;i<it;++i) data.push_back(distribution(gen));
        return;
    }
    if(simulationType==modelli{costante}){
        for(unsigned int i=0;i<it;++i) data.push_back((max+min)/2);
    }
}

std::vector<double> Sensor::getData() const{
    return data;
}

Sensor::Sensor(const std::string& nome,const modelli& mod):name(nome),simulationType(mod)
    ,min(-10),max(10){}

Sensor::~Sensor(){}
