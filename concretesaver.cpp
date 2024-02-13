#include "concretesaver.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>
#include <QJsonDocument>

#include "uvsensor.h"
#include "humiditysensor.h"
#include "windsensor.h"
#include "error.h"


enum SensorString{uvSensor,humiditySensor,windSensor};

ConcreteSaver::ConcreteSaver(const std::string& saddress,const std::string& laddress)
    :saveAddress(saddress),loadAdderss(laddress){}

ConcreteSaver::~ConcreteSaver(){}

void ConcreteSaver::save(const std::string& addr)const{
    std::string effAddr= addr==""?saveAddress:addr;
    if(effAddr=="")throw Error(1);

    QFile file(QString::fromStdString(effAddr));
    QJsonObject dati;
    dati["lista sensori"]=data;
    QJsonDocument doc(dati);
    if(file.open(QIODevice::WriteOnly | QIODevice:: Text)){
        QTextStream out(&file);
        out<<doc.toJson();
        file.close();
    } else{
        file.close();
        throw Error(3);
    }
}

std::list<Sensor*> ConcreteSaver::load(const std::string& addr)const{
    std::string effAddr=addr==""?loadAdderss:addr;
    if(effAddr=="")throw Error(1);

    QFile file(QString::fromStdString(effAddr));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){throw Error(3);}
    QJsonParseError JsonError;
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll(),&JsonError);
    file.close();

    if(JsonError.error != QJsonParseError::NoError) throw Error(4);
    if(!doc.isObject()) return std::list<Sensor*>();

    //contiene l'effettivo oggetto json
    QJsonObject obj=doc.object();
    if(obj.contains("lista sensori") && obj.value("lista sensori").isArray()){
        //array dei sensori
        QJsonArray sensori=obj.take("lista sensori").toArray();
        std::list<Sensor*> ret;
        for(unsigned int i=0;i<sensori.size();++i){

            QJsonObject obj=sensori[i].toObject();
            if(obj.contains("type")){
                if(obj.value("type").toInt()==SensorString{uvSensor})
                    loadUVSensor(ret,obj);
                else if(obj.value("type").toInt()==SensorString{humiditySensor})
                    loadHumiditySensor(ret,obj);
                else if(obj.value("type").toInt()==SensorString{windSensor})
                    loadWindSensor(ret,obj);
            }
        }
        return ret;
    }
    else return std::list<Sensor*>();
}

void ConcreteSaver::deleteData(){
    while(!data.empty()) data.pop_back();
}


//metodi getter e setter
void ConcreteSaver::setsAddress(const std::string& address){saveAddress=address;}
void ConcreteSaver::setlAddress(const std::string& address){loadAdderss=address;}
std::string ConcreteSaver::getsAddress() const{return saveAddress;}
std::string ConcreteSaver::getlAddress() const{return loadAdderss;}


void ConcreteSaver::saveUVSensor(const UVSensor& sen){
    QJsonArray JsonDati;

    std::vector<double> dati=sen.getData();
    for(double val:dati) JsonDati.append(val);

    QJsonObject oggetto;
    oggetto["dati"]=JsonDati;
    oggetto["simType"]=sen.getSimulator();
    oggetto["name"]=QString::fromStdString(sen.getName());
    oggetto["type"]=SensorString{uvSensor};
    oggetto["min"]=sen.getMin();
    oggetto["max"]=sen.getMax();
    data.append(oggetto);
}
void ConcreteSaver::saveHumiditysensor(const HumiditySensor& sen){
    QJsonArray JsonDati;
    std::vector<double> dati=sen.getData();

    for(double val:dati) JsonDati.append(val);

    QJsonObject oggetto;//Rappresentazione del sensore in Json
    oggetto["dati"]=JsonDati;
    oggetto["simType"]=sen.getSimulator();
    oggetto["name"]=QString::fromStdString(sen.getName());
    oggetto["type"]=SensorString{humiditySensor};
    oggetto["min"]=sen.getMin();
    oggetto["max"]=sen.getMax();
    data.append(oggetto);
}
void ConcreteSaver::saveWindSensor(const WindSensor& sen){
    std::vector<double> dati=sen.getData();
    std::vector<unsigned int> direzioni=sen.getWindDirections();

    unsigned int iterazioni=std::min(dati.size(),direzioni.size());

    QJsonArray JsonDati;//Contiene le coppie intensità del vento e direzione
    for(unsigned int i=0;i<iterazioni;++i){
        QJsonObject temp;
        temp["dir"] = int(direzioni[i]);
        temp["value"] = dati[i];
        JsonDati.append(temp);
    }

    QJsonObject oggetto; //Rappresentazione del sensore in Json
    oggetto["dati"]=JsonDati;
    oggetto["simType"]=sen.getSimulator();
    oggetto["name"]=QString::fromStdString(sen.getName());
    oggetto["type"]=SensorString{windSensor};
    oggetto["min"]=sen.getMin();
    oggetto["max"]=sen.getMax();
    data.append(oggetto);
}

void ConcreteSaver::loadUVSensor(std::list<Sensor*>& ret,QJsonObject& obj)const{
    Sensor* sen=new UVSensor(obj.take("name").toString().toStdString());
    ret.push_front(sen);
    sen->setMin(obj.take("min").toDouble());
    sen->setMax(obj.take("max").toDouble());
    int a=obj.take("simType").toInt();
    if(a==modelli{normale}) sen->setSimulationType(modelli{normale});
    else if(a==modelli{uniforme}) sen->setSimulationType(modelli{uniforme});
    else if(a==modelli{costante}) sen->setSimulationType(modelli{costante});

    QJsonArray data=obj.take("dati").toArray();
    std::vector<double> val;

    for(auto it=data.begin();it<data.end();++it) val.push_back(it->toDouble());
    sen->data=val;
}

void ConcreteSaver::loadHumiditySensor(std::list<Sensor*>& ret,QJsonObject& obj)const{
    Sensor* sen=new HumiditySensor(obj.take("name").toString().toStdString());
    ret.push_front(sen);
    sen->setMin(obj.take("min").toDouble());
    sen->setMax(obj.take("max").toDouble());
    int a=obj.take("simType").toInt();
    if(a==modelli{normale}) sen->setSimulationType(modelli{normale});
    else if(a==modelli{uniforme}) sen->setSimulationType(modelli{uniforme});
    else if(a==modelli{costante}) sen->setSimulationType(modelli{costante});

    QJsonArray data=obj.take("dati").toArray();
    std::vector<double> val;
    for(auto it=data.begin();it<data.end();++it) val.push_back(it->toDouble());
    sen->data=val;
}

void ConcreteSaver::loadWindSensor(std::list<Sensor*>& ret,QJsonObject& obj)const{
    WindSensor* sen=new WindSensor(obj.take("name").toString().toStdString());
    ret.push_front(sen);
    sen->setMin(obj.take("min").toDouble());
    sen->setMax(obj.take("max").toDouble());
    int a=obj.take("simType").toInt();
    if(a==modelli{normale}) sen->setSimulationType(modelli{normale});
    else if(a==modelli{uniforme}) sen->setSimulationType(modelli{uniforme});
    else if(a==modelli{costante}) sen->setSimulationType(modelli{costante});

    QJsonArray data=obj.take("dati").toArray();
    std::vector<double> val;
    std::vector<unsigned int> dir;
    for(unsigned int i=0;i<data.size();++i){
        QJsonObject obj=data[i].toObject();
        val.push_back(obj.take("value").toDouble());
        dir.push_back(obj.take("dir").toInt());
    }
    sen->data=val;
    sen->directions=dir;
}
