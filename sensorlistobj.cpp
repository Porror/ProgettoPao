#include "sensorlistobj.h"
#include <QMouseEvent>
#include <QGridLayout>

SensorListObj::SensorListObj(const QString& str,QWidget *parent):
    QWidget{parent},icon(new QIcon()),iconlabel(new QLabel(this)),nome(new QLabel(str,this)),updButton(new QPushButton("mostra",this)){

    update();

    QGridLayout* layout=new QGridLayout(this);
    layout->addWidget(iconlabel,0,0);
    layout->addWidget(nome,0,1);
    layout->addWidget(updButton,1,0);

    this->setLayout(layout);
    connect(updButton,SIGNAL(clicked(bool)),this,SLOT(emissione()));
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

void SensorListObj::updateName(const std::string& str){
    nome->setText(QString::fromStdString(str));
    nome->update();
}

void SensorListObj::updateVal(const Sensor*){}

void SensorListObj::update(){
    iconlabel->setPixmap(icon->pixmap(20,20));
}

void SensorListObj::emissione(){
    emit click(this);
}
