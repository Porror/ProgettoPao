#include "uvsensor.h"
#include "error.h"

UVSensor::UVSensor(const std::string& nome,const modelli& mod):Sensor(nome,mod){
    min=minscale;
    max=maxscale;
}

UVSensor::~UVSensor(){}

void UVSensor::simulate(unsigned int iterations){
    if(min!=int(min) && max!=int(max)) throw Error(1);
    //verifico che i valori siano contenuti nella scala
    if(min<minscale || max>maxscale) throw Error(2);

    try{
        Sensor::simulate(iterations);
    }
    catch(Error e){
        throw Error(e);
    }

    //Per mantenere la media coerente con quella calcolata in precedenza
    for(double& i:data){
        if(i>=int(i)+0.5) i=int(i)+1;
        else i=int(i);
    }
}

void UVSensor::save(Saver*sav)const{
    sav->saveUVSensor(*this);
}


void UVSensor::setMin(const double& m){
    if(m==int(m) && m>=minscale && m<=maxscale) min=m;
}

void UVSensor::setMax(const double& m){
    if(m==int(m) && m>=minscale && m<=maxscale) min=m;
}
