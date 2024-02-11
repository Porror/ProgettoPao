#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include "Sensor.h"

class createwindow:public QWidget
{
    Q_OBJECT
private:
    Sensor* s;
    QLineEdit* minEdit;
    QLineEdit* maxEdit;
    QLineEdit* nameEdit;
    QComboBox* modelloSelector;

    QComboBox* sensorSelector;
public:
    createwindow(Sensor* s=nullptr,QWidget* parent=nullptr);
    ~createwindow();
private slots:
    void collegaModifica();
    void collegaCrea();
signals:
    void modifica(Sensor*,QString,int,int,modelli);//riturna s,nome,minimo, massimo e modello
    void crea(QString,int,int,int,modelli);//ritorna nome, tipo,minimo, massimo e modello
};

#endif // CREATEWINDOW_H
