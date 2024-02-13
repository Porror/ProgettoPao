#include "mainwindowsensor.h"
#include <QIntValidator>

MainWindowSensor::MainWindowSensor(QWidget *parent)
    : QWidget{parent}, nome(new QLabel(this)), modificaDati(new QPushButton("modifica dati",this)),
    simula(new QPushButton("simula",this)),numsim(new QLineEdit(this)), mainlayout(new QGridLayout){

    numsim->setValidator(new QIntValidator(2,1000));
    numsim->setText("5");

    mainlayout->setObjectName("Layout mainWindowSensor");
    mainlayout->addWidget(nome,0,0);
    mainlayout->addWidget(modificaDati,0,1);
    mainlayout->addWidget(numsim,1,0);
    mainlayout->addWidget(simula,1,1);
    this->setLayout(mainlayout);

    connect(modificaDati,SIGNAL(clicked(bool)),this,SLOT(slotModifica()));
    connect(simula,SIGNAL(clicked(bool)),this,SLOT(slotSimula()));
}


MainWindowSensor::~MainWindowSensor(){
    delete nome;
    delete modificaDati;
    delete simula;
}

void MainWindowSensor::updateName(const std::string& name){
    nome->setText(QString::fromStdString(name));
    nome->show();
}

void MainWindowSensor::setName(const QString& name){
    nome->setText(name);
}

void MainWindowSensor::slotModifica(){
    emit modificaPremuta();
}

void MainWindowSensor::slotSimula(){
    emit simulaPreuta(numsim->text().toInt());
}
