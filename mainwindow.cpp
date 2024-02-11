#include "mainwindow.h"

#include <QLineEdit>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),sensori({}),mainlayout(new QHBoxLayout),leftlayout(new QVBoxLayout),sensorsScrollArea(new QScrollArea(this)),
    sensorsLayout(new QVBoxLayout(this)),sensor(nullptr),saveAction(new QAction("Salva", this)),loadAction(new QAction("Carica",this)),
    modificaAction(new QAction("Modifica",this)),eliminaAction(new QAction("Elimina",this)),newSensorAction(new QAction("Nuovo",this))
{
    QWidget* mainwidget=new QWidget; //permette di inserire un layout nalla mainwindow, non è possibile altrimenti
    this->setCentralWidget(mainwidget);
    mainlayout->setObjectName("mainlayout");

    this->setMinimumSize(500,300);

    mainwidget->setLayout(mainlayout);
    leftlayout->setObjectName("left layout");
    mainlayout->addLayout(leftlayout);

    //Barra di ricerca nella barra superiore sinistra dello schermo
    QLineEdit* ricerca=new QLineEdit();
    leftlayout->addWidget(ricerca);
    ricerca->setClearButtonEnabled(true);
    ricerca->setPlaceholderText("Ricerca...");
    ricerca->setMinimumSize(100,20);
    ricerca->setMaximumSize(200,20);

    //layout scheda sensori sinistra
    sensorsScrollArea->setMinimumWidth(100);
    sensorsScrollArea->setMaximumWidth(200);
    leftlayout->addWidget(sensorsScrollArea);

    //creazione menù
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(loadAction);
    fileMenu->addAction(modificaAction);
    fileMenu->addAction(eliminaAction);
    fileMenu->addAction(newSensorAction);

    connect(ricerca,&QLineEdit::textChanged,this,&MainWindow::search);
}

MainWindow::~MainWindow(){}//non necessito di distruggere puntatori in quanto lo fà già Qt

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

void MainWindow::addsensor(SensorListObj*sen){
    if(!sensori.empty()){
        for(auto i:sensori) if(i==sen) return;
        sensori.push_back(sen);
    }
    else sensori.push_back(sen);
    sensorsScrollArea->setLayout(sensorsLayout);
    sensorsLayout->addWidget(sen);
    qDebug()<<"sensore aggiunto alla coda?\n";

}

void MainWindow::removesensor(SensorListObj* sen){
    for(auto i=sensori.begin();i<sensori.end();++i){
        if(*i==sen){
            delete *i;
            sensori.erase(i);
        }
    }
    sensorsLayout->removeWidget(sen);
    sensorsLayout->update();
}

void MainWindow::addSensorMain(MainWindowSensor* sen){
    if(sensor==sen) return;
    delete sensor;
    sensor=sen;
}

