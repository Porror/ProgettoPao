#include "controller.h"
#include <QFile>
#include <qjsondocument>
#include <QJsonArray>


controller::controller() {}
void controller::save() const{
}

void controller::updateName(const std::string& nome,std::list<Observer*> observers){
    for(Observer* observer:observers) observer->updateName(nome);
}

void controller::updateVal(std::list<Observer*> observers,Sensor* sensor) const{
    for(Observer* observer:observers) observer->updateVal(sensor);
}

void controller::attach(Observer* obs,const Sensor* sen){
    //itera sulla lista di Observer corrispondente al sensore sen
    for(std::pair<Sensor*,std::list<Observer*>>& coppia:sensors){
        if(coppia.first==sen){
            //Verifico se obs è già presente nella lista, altrimenti lo aggiungo
            for(Observer* observer:coppia.second) if(observer==obs)return;
            coppia.second.push_front(obs);
        }
    }
}

void controller::detach(Observer* obs,const Sensor* sen){
    //itera sulla lista di Observer corrispondente al sensore sen
    for(std::pair<Sensor*,std::list<Observer*>>& coppia:sensors){
        if(coppia.first==sen) coppia.second.remove(obs);
    }
}
