#include "humiditysensor.h"
#include "error.h"

HumiditySensor::HumiditySensor(const std::string& nome,const modelli& mod):Sensor(nome,mod){
    min=minscale;
    max=maxscale;
}

HumiditySensor::~HumiditySensor(){}

void HumiditySensor::simulate(unsigned int iterations){
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

void HumiditySensor::save(Saver*sav)const{
    sav->saveHumiditysensor(*this);
}

void HumiditySensor::setMin(const double& m){
    if(m==int(m) && m>=minscale && m<=maxscale) min=m;
}

void HumiditySensor::setMax(const double& m){
    if(m==int(m) && m>=minscale && m<=maxscale) min=m;
}
