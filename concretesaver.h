#ifndef CONCRETESAVER_H
#define CONCRETESAVER_H

#include "Saver.h"
#include "Sensor.h"
#include <QJsonArray>
#include <QJsonObject>

class ConcreteSaver : public Saver
{
private:
    std::string saveAddress;
    std::string loadAdderss;
    //constiene la lista di sensori da salvare
    QJsonArray data;
    //aggiungono i dati al QJsonArray data
    void saveUVSensor(const UVSensor&) override;
    void saveHumiditysensor(const HumiditySensor&) override;
    void saveWindSensor(const WindSensor&) override;
    //utilizzate come funzioni di supporto a load
    void loadUVSensor(std::list<Sensor*>&,QJsonObject&) const;
    void loadHumiditySensor(std::list<Sensor*>&,QJsonObject&) const;
    void loadWindSensor(std::list<Sensor*>&,QJsonObject&) const;
public:
    ConcreteSaver(const std::string& saddress="",const std::string& laddress="");
    void save(const std::string& address="")const;//effettua l'effettivo salvataggio
    std::list<Sensor*> load(const std::string& address="")const;//effettua il caricamento
    void deleteData();
    void setsAddress(const std::string&);
    void setlAddress(const std::string&);
    std::string getsAddress() const;
    std::string getlAddress() const;
    ~ConcreteSaver()override;
};

#endif // CONCRETESAVER_H
