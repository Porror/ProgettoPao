#include "mainwindow.h"

#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),mainlayout(new QHBoxLayout),sensor(nullptr)
{

    this->setLayout(mainlayout);
    QVBoxLayout* leftlayout = new QVBoxLayout();
    mainlayout->addLayout(leftlayout);

    //Barra di ricerca nella barra superiore sinistra dello schermo
    QLineEdit* ricerca=new QLineEdit();
    leftlayout->addWidget(ricerca);
    ricerca->setClearButtonEnabled(true);
    ricerca->setPlaceholderText("Ricerca...");
    ricerca->setMinimumSize(100,20);

    //layout scheda sensori sinistra
    QVBoxLayout* sensorslayout=new QVBoxLayout;
    leftlayout->addLayout(sensorslayout);



    connect(ricerca,&QLineEdit::textChanged,this,&MainWindow::search);
}

MainWindow::~MainWindow()
{
}

void MainWindow::search(const QString& nome){
    if(nome==""){
        for(auto s:sensori) s->show();
    }
    else{
        for(auto s:sensori){
            if(s->getName().contains(nome))s->show();
            else s->hide();
        }
    }
}
