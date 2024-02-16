#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sensorlistobj.h"
#include <QHBoxLayout>
#include "mainwindowsensor.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class presenter;
private:
    std::list<SensorListObj*> sensori; //lista dei sensori contenuti nella mainwinvdow (a sinistra)
    QHBoxLayout* mainlayout;
    QVBoxLayout* leftlayout;
    QVBoxLayout* sensorsLayout;
    MainWindowSensor * sensor; //sensore contenuto nella parte principale della finestra
    //azioni disponibili nel menu di cui si occupa il presenter
    QAction *saveAction; //permette di caricare un file json
    QAction *loadAction; //permette di salvare un file json
    QAction *modificaAction; //permette di modificare il sensore attualmente visualizzato
    QAction *eliminaAction; //Permette di eliminare il sensore attualmente visualizzato
    QAction *newSensorAction; //Permette di aggiungere un nuovo sensore
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addSensorMain(MainWindowSensor*); //si occupa anche di distruggere l'oggetto visualizzato se presente
    void addsensor(SensorListObj*);//agiunge un elemento alla lista di sensori
    void removesensor(SensorListObj*); //si occupa di rimuove l'oggetto dalla lista di sensori
private slots:
    void search(const QString& nome);
};

#endif // MAINWINDOW_H
