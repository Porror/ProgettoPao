#include "presenter.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "error.h"
#include <QFileDialog>
#include <QErrorMessage>
#include "createwindow.h"

#include "qobjectdefs.h"
#include "uvsensor.h"
#include "humiditysensor.h"
#include "windsensor.h"

#include "sensorlistuv.h"
#include "sensorlisthum.h"
#include "sensorlistwind.h"

#include "mainwinuv.h"
#include "mainwinhum.h"
#include "mainwinwind.h"

presenter::presenter(ConcreteSaver* sav,MainWindow* win,QWidget* parent):QWidget{parent}, s(sav),window(win){

    connect(window->saveAction,SIGNAL(triggered(bool)),this,SLOT(savedialog()));
    connect(window->loadAction,SIGNAL(triggered(bool)),this,SLOT(loaddialog()));
    connect(window->modificaAction,SIGNAL(triggered(bool)),this,SLOT(modificaselezionato()));
    connect(window->eliminaAction,SIGNAL(triggered(bool)),this,SLOT(eliminaselezionato()));
    connect(window->newSensorAction,SIGNAL(triggered(bool)),this,SLOT(newSensor()));
}

presenter::~presenter(){
    delete s;
    delete window;
}

void presenter::error(const QString& str){
    QWidget* errore=new QWidget(nullptr);//Pagina da mostrare
    QVBoxLayout* layout=new QVBoxLayout(errore);//Layout pagina di errore
    errore->setWindowTitle("Errore");//Titolo della Pagina
    QLabel* errormessage=new QLabel(errore);//Messaggio di errore
    errormessage->setText(str);
    QPushButton* closeButton=new QPushButton("Chiudi",errore);//Bottone di chiusura

    connect(closeButton,SIGNAL(clicked(bool)),errore,SLOT(close()));

    layout->addWidget(errormessage);
    layout->addWidget(closeButton);
    errore->setLayout(layout);

    errore->show();
}

std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator presenter::getiterator(const Sensor* sen){
    for(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator i=sensors.begin();i<sensors.end();++i){
        if(i->first==sen) return i;
    }
    return sensors.end();
}

std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator presenter::getiterator(const Observer* obs){
    for(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator i=sensors.begin();i<sensors.end();++i){
        for(auto li:i->second) if(li==obs) return i;
    }
    return sensors.end();
}

void presenter::save(){
    for(unsigned int i=0;i<sensors.size();++i){
        sensors[i].first->save(s);
    }
    try{
        s->save();
    }
    catch(Error e){
        error(QString::fromStdString(e.correspondingString()));
    }
    catch(...){error("Errore sconosciuto");}
}

void presenter::savedialog(){
    QString fileName=QFileDialog::getSaveFileName(window,"File in cui desideri salvare i dati","../","Text Files (*.json);;All Files (*)");
    if(!fileName.endsWith(".json"))return;
    s->setsAddress(fileName.toStdString());
    save();
}

void presenter::load(){
    std::list<Sensor*> listaObs;
    try{
    listaObs=s->load();
    }
    catch(Error e){
        error(QString::fromStdString(e.correspondingString()));
    }
    catch(...){error("Errore sconosciuto");}

    while(!listaObs.empty()){
        Sensor *sen=listaObs.front();
        listaObs.pop_front();
        SensorListObj* listsen = nullptr;
        //verifico il tipo effettivo del sensore
        if(dynamic_cast<UVSensor*>(sen))
            listsen=new SensorListUV(QString::fromStdString(sen->getName()));
        else if(dynamic_cast<HumiditySensor*>(sen))
            listsen= new SensorListHum(QString::fromStdString(sen->getName()));
        else if(dynamic_cast<WindSensor*>(sen))
            listsen= new SensorListWind(QString::fromStdString(sen->getName()));
        else
            error("Tipo di sensore non riconosciuto, aggiornare il presenter");
        if(listsen){
            window->addsensor(listsen);
            sensors.push_back(std::pair<Sensor*,std::list<Observer*>>{sen,{listsen}});
            connect(listsen,SIGNAL(click(Observer*)),this,SLOT(dclwork(Observer*)));
        }
    }
}

void presenter::dclwork(Observer* obs){
    Sensor* sen=getiterator(obs)->first;
    attach(obs,sen);
    MainWindowSensor* newsensor=nullptr;
    //Scelta del costruttore corretto
    if(dynamic_cast<UVSensor*>(sen)) newsensor = new MainWinUv();
    else if(dynamic_cast<HumiditySensor*>(sen)) newsensor = new MainWinHum();
    else if(dynamic_cast<WindSensor*>(sen)) newsensor = new MainWinWind();
    else error("Tipo di sensore non riconosciuto, aggiornare il presenter");

    if(newsensor){
        newsensor->setName(QString::fromStdString(sen->getName()));
        if(window->sensor){
            detach(window->sensor,sen); //stacco l'observer da rimuovere
            window->mainlayout->removeWidget(window->sensor);
            delete window->sensor;
        }
        window->sensor=newsensor;
        window->mainlayout->addWidget(newsensor);
        attach(newsensor,sen);
        window->mainlayout->update();
        newsensor->updateVal(sen);
    }

    connect(window->sensor,SIGNAL(modificaPremuta()),this,SLOT(modificaselezionato()));
    connect(window->sensor,SIGNAL(simulaPreuta(uint)),this,SLOT(simulaselezionato(uint)));
}

void presenter::loaddialog(){
    QString filename=QFileDialog::getOpenFileName(window,"File da cui desideri importare i dati","../","Text Files (*.json)");
    s->setlAddress(filename.toStdString());
    load();
}

void presenter::updateName(const std::string& nome,std::list<Observer*> observers){
    for(Observer* observer:observers) observer->updateName(nome);
}

void presenter::updateVal(std::list<Observer*> observers,Sensor* sensor) const{
    for(Observer* observer:observers) observer->updateVal(sensor);
}


void presenter::attach(Observer* obs,Sensor* sen){
    //itera sulla lista di fino a Observer i per elementi vector, iter per elementi coda
    for(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator i=sensors.begin();i<sensors.end();++i){
        if(i->first==sen){
            bool present=false;
            for(auto iter:i->second){
                if(iter==obs)present=true;
            }
            if(false==present) i->second.push_front(obs);
        }
    }
}

void presenter::detach(Observer* obs,Sensor* sen){
    //itera fino all'elemento obs nel vettore
    for(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator i=sensors.begin();i<sensors.end();++i){
        if(i->first==sen){
            i->second.remove(obs);
            return;
        }
    }
}


void presenter::remove(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator it){
    //Distruggo gli observer (se elimino il sensore tutti gli observer del sensore vanno eliminati)
    while(!it->second.empty()){
        delete it->second.front();
        it->second.pop_front();
    }
    delete (*it).first; //elimino il sensore
    sensors.erase(it); //rimuovo l'elemento che conteneva il sensore
}

void presenter::modifydialog(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator it){
    createwindow* modificawindow=new createwindow(it->first);
    connect(modificawindow,SIGNAL(modifica(Sensor*,QString,int,int,modelli)),this,SLOT(modify(Sensor*,QString,int,int,modelli)));
    modificawindow->show();
}

void presenter::modificaselezionato(){
    if(!window->sensor) error("seleziona un sensore per modificarlo");
    //proseguo sapendo che esiste un sensore attalmente selezionato
    else modifydialog(getiterator(window->sensor));
}


void presenter::modify(Sensor* sen,QString nome,int min,int max,modelli mod){
    try{
        auto it=getiterator(sen);
        if(it!=sensors.end()){
            it->first->setName(nome.toStdString());
            it->first->setMin(min);
            it->first->setMax(max);
            it->first->setSimulationType(mod);
            for(auto i:it->second)i->updateName(nome.toStdString());
        }
    }catch(...){}
}

void presenter::aggiungiSensore(QString nome ,int tipo,int min,int max,modelli mod){
    SensorListObj* selliobj=nullptr;
    Sensor* sen=nullptr;
    if(tipo==0){ //UVSensor
        selliobj=new SensorListUV(nome);
        sen=new UVSensor(nome.toStdString(),mod);
    }
    else if(tipo==1){//WindSensor
        selliobj=new SensorListWind(nome);
        sen=new WindSensor(nome.toStdString(),mod);
    }
    else{//HumiditySensor
        selliobj=new SensorListHum(nome);
        sen=new HumiditySensor(nome.toStdString(),mod);
    }
    sen->setMax(max);
    sen->setMin(min);
    window->addsensor(selliobj);
    //aggiungo il sensore alla lista di sensori del presenter
    sensors.push_back(std::pair<Sensor*,std::list<Observer*>>{sen,std::list<Observer*>{selliobj}});
    connect(selliobj,SIGNAL(click(Observer*)),this,SLOT(dclwork(Observer*)));
    window->leftlayout->update();
}

void presenter::eliminaselezionato(){
    if(!window->sensor)return;
    auto presenterit=getiterator(window->sensor);
    while(presenterit->second.size()>0){
        auto listit=presenterit->second.begin();
        if(dynamic_cast<SensorListObj*>(*listit))window->removesensor(dynamic_cast<SensorListObj*>(*listit));
        else if(*listit==window->sensor){
            window->mainlayout->removeWidget(window->sensor);
            window->sensor=nullptr;
        }
        delete *listit;
        detach(*listit,presenterit->first);
    }
    delete presenterit->first;
    sensors.erase(presenterit);
}

void presenter::newSensor(){
    createwindow* w=new createwindow();
    w->show();
    connect(w,SIGNAL(crea(QString,int,int,int,modelli)),this,SLOT(aggiungiSensore(QString,int,int,int,modelli)));
}

void presenter::simulaselezionato(unsigned int iterazioni){
    auto it=getiterator(window->sensor);
    it->first->simulate(iterazioni);
    for(auto i=it->second.begin();i!=it->second.end();++i){
        (*i)->updateVal(it->first);
    }
}
