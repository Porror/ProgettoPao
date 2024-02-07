#include "sensorlistobj.h"
#include <qboxlayout>

SensorListObj::SensorListObj(const QString& str,QWidget *parent):
    QWidget{parent},icon(new QIcon()),iconlabel(new QLabel),nome(new QLabel(str)){

    update();

    QHBoxLayout* layout=new QHBoxLayout;
    layout->addWidget(iconlabel);
    layout->addWidget(nome);

    this->setLayout(layout);
}

SensorListObj::~SensorListObj(){}

void SensorListObj::setIcon(const QString& str){
    icon->addFile(str);
}

QString SensorListObj::getName()const{
    return nome->text();
}

void SensorListObj::setNome(const QString& str){
    nome->setText(str);
    update();
}

void SensorListObj::update(){
    iconlabel->setPixmap(icon->pixmap(20,20));
}
