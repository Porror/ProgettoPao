#ifndef PRESENTER_H
#define PRESENTER_H

#include "Sensor.h"
#include <list>
#include <string>
#include "Observer.h"
#include "concretesaver.h"
#include "mainwindow.h"

class presenter:public QWidget
{
    Q_OBJECT
private:
    ConcreteSaver* s;
    MainWindow* window;
    std::vector<std::pair<Sensor*,std::list<Observer*>>> sensors;

    void updateName(const std::string&,std::list<Observer*>);//chiama il metodo Updatename per tutti gli observer di un sensor
    void updateVal(std::list<Observer*>,Sensor*) const;//chiama il metodo Updateval per tutti gli observer di un sensor

    void attach(Observer*,Sensor*);//collega Observer a corrispettivo Sensor
    void detach(Observer*,Sensor*);//rimuove un observer dal sensore

    void save();//effettua il salvataggio effettivo, di supporto per savedialog()
    void load();//effettua il caricamento dei dati
    void modifydialog(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator);// crea la QDialog di modifica sensore e effettua la modifica

    std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator getiterator(const Sensor*);
    std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator getiterator(const Observer*);

    void error(const QString& str);

    void remove(std::vector<std::pair<Sensor*,std::list<Observer*>>>::iterator);//effettua l'eliminazione di un sensore
public:
    presenter(ConcreteSaver*,MainWindow*,QWidget* parent=nullptr);
    ~presenter();
public slots:
    void savedialog();//crea la QDialog di salvataggio e chiama save()
    void loaddialog();//crea la QDialog di caricamento e chiana loa()
    void modify(Sensor*,QString,int,int,modelli mod);//esegue la modifica di un dato sensore
    void modificaselezionato();//modifica il sensore nella mainwindow
    void eliminaselezionato();//elimina il sensore nella mainwindow
    void simulaselezionato(unsigned int);//simula il sensore selezionato
    void dclwork(Observer*); //connessione clic bottone mostra
    void aggiungiSensore(QString,int,int,int,modelli);//effettua l'aggiunta
private slots:
    void newSensor();//crea la dialog di aggiunta sensore e la connette a aggiungiSensore
};

#endif // PRESENTER_H
