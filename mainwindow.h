#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sensorlistobj.h"
#include <QHBoxLayout>
#include <QScrollArea>
#include "mainwindowsensor.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class controller;
private:
    std::vector<SensorListObj*> sensori; //lista dei sensori contenuti nella mainwinvdow (a sinistra)
    QHBoxLayout* mainlayout;
    QVBoxLayout* leftlayout;
    QScrollArea* sensorsScrollArea;
    QVBoxLayout* sensorsLayout;
    MainWindowSensor * sensor; //sensore contenuto nella parte principale della finestra
    //azioni disponibili nel menu di cui si occupa il controller
    QAction *saveAction; //permette di caricare un file json
    QAction *loadAction; //permette di salvare un file json
    QAction *modificaAction; //permette di modificare il sensore attualmente visualizzato
    QAction *eliminaAction; //Permette di eliminare il sensore attualmente visualizzato
    QAction *newSensorAction; //Permette di aggiungere un nuovo sensore
public:
    void addSensorMain(MainWindowSensor*); //si occupa anche di distruggere l'oggetto visualizzato se presente
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addsensor(SensorListObj*);
    void removesensor(SensorListObj*); //si occupa di distruggere l'oggetto
private slots:
    void search(const QString& nome);
};

#endif // MAINWINDOW_H
