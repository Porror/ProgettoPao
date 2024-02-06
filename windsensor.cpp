#include "windsensor.h"
#include "error.h"
#include <random>
#include <time.h>

//Da rimuovere
#include <iostream>

unsigned int WindSensor::maxangle=364;
unsigned int WindSensor::minangle=0;

WindSensor::WindSensor(const std::string& nome,const modelli& mod):Sensor(nome,mod){
    min=0;
    max=100;
}

WindSensor::~WindSensor(){}

void WindSensor::simulate(unsigned int iterazioni){

    if(min!=int(min) && max!=int(max)) throw Error(1);
    if(min<0) throw Error(2);

    try{
        Sensor::simulate(iterazioni);
    }
    catch(Error e){
        throw Error(e);
    }
    for(unsigned int i=0;i<data.size();++i){
        if(data[i]>=int(data[i])) data[i]=int(data[i]+1);
        else data[i]=int(data[i]);
    }

    if(!directions.empty()) directions.clear();

    std::random_device rd;
    std::mt19937 gen(rd());

    if(simulationType != modelli{costante}){
        srand(time(NULL));
        for(unsigned int i=0;i<iterazioni;++i)directions.push_back((std::rand()%(maxangle-minangle))+minangle);
        return;
    }
    else{for(unsigned int i=0;i<iterazioni;++i)directions.push_back(180);}
}

std::vector<unsigned int> WindSensor::getWindDirections() const{
    return directions;
}

void WindSensor::save(Saver*sav)const{
    sav->saveWindSensor(*this);
}

void WindSensor::setMin(const double& m){
    if(m==int(m) && m>=0) min=m;
}

void WindSensor::setMax(const double& m){
    if(m==int(m) && m>=0) min=m;
}

