#include "mainwindowsensor.h"

MainWindowSensor::MainWindowSensor(QWidget *parent)
    : QWidget{parent}, nome(new QLabel()), modificaDati(new QPushButton("modifica dati")),
    simula(new QPushButton("simula")), mainlayout(new QVBoxLayout){

    mainlayout->setObjectName("Layout mainWindowSensor");
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setObjectName("Layout bottoni mainWindowSensor");
    layout->addWidget(nome);
    layout->addWidget(modificaDati);
    layout->addWidget(simula);
    mainlayout->addLayout(layout);
    this->setLayout(mainlayout);
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




