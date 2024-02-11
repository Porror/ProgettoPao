#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Sensor.h"
#include <list>
#include <string>
#include "Observer.h"
#include "concretesaver.h"
#include "mainwindow.h"

class controller:public QWidget
{
    Q_OBJECT
private:
    ConcreteSaver* s;
    MainWindow* window;
    std::vector<std::pair<Sensor*,std::list<Observer*>>> sensors;

    void updateName(const std::string&,std::list<Observer*>);
    void updateVal(std::list<Observer*>,Sensor*) const;

    void attach(Observer*,Sensor*);//collega Observer a corrispettivo Sensor tramite attachdir
    void attachdir(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator,const Observer*);
    void detach(Observer*,Sensor*);//rimuove un observer dal sensore tramite detachdir
    void detachdir(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator,const Observer*);

    void savedialog();//crea la QDialog di salvataggio e chiama save()
    void modifydialog(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator);// crea la QDialog di modifica sensore e effettua la modifica
    void loaddialog();//crea la QDialog di caricamento e chiana loa()

    std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator getiterator(const Sensor*);
    std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator getiterator(const Observer*);

    void error(const QString& str);

    void remove(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator);//effettua l'eliminazione di un sensore
public:
    controller(ConcreteSaver*,MainWindow*,QWidget* parent=nullptr);
    ~controller();
public slots:
    void save();//effettua il salvataggio effettivo, di supporto per savedialog()
    void load();//effettua il caricamento dei dati
    void modify(Sensor*,QString,int,int,modelli mod);
    void modificaselezionato();//modifica il sensore nella mainwindow
    void eliminaselezionato();//elimina il sensore nella mainwindow
    void dclwork(Observer*); //Connessione da fare a DC su item lista Sensori
    void aggiungiSensore(QString,int,int,int,modelli mod);//effettua l'aggiunta
private slots:
    void newSensor();//crea la dialog di aggiunta sensore e la connette a aggiungiSensore
};

#endif // CONTROLLER_H
