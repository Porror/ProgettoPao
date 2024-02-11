#include "createwindow.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QIntValidator>

createwindow::~createwindow(){
    if(s) delete s;
}

createwindow::createwindow(Sensor* sen,QWidget*parent):QWidget{parent},s(sen),minEdit(new QLineEdit(this))
    ,maxEdit(new QLineEdit(this)),nameEdit(new QLineEdit(this)),modelloSelector(new QComboBox(this)),sensorSelector(new QComboBox(this)){

    this->setMinimumSize(400,300);
    QGridLayout* layout=new QGridLayout(this); //layout pagina
    this->setLayout(layout);

    minEdit->setValidator(new QIntValidator(minEdit));
    maxEdit->setValidator(new QIntValidator(maxEdit));

    modelloSelector->addItem("Normale");
    modelloSelector->addItem("Costante");
    modelloSelector->addItem("Uniforme");

    //Divisione tra creazione e modifica sensore
    if(s){
        sensorSelector->hide();
        this->setWindowTitle("Modifica sensore");
        if(s->getSimulator()==modelli{normale}) modelloSelector->setCurrentIndex(0);
        else if(s->getSimulator()==modelli{costante}) modelloSelector->setCurrentIndex(1);
        else modelloSelector->setCurrentIndex(2);
        minEdit->setText(QString::number(s->getMin()));
        minEdit->setClearButtonEnabled(true);
        maxEdit->setText(QString::number(s->getMax()));
        maxEdit->setClearButtonEnabled(true);
        nameEdit->setText(QString::fromStdString(s->getName()));
        nameEdit->setClearButtonEnabled(true);
    }
    else{
        this->setWindowTitle("Creazione sensore");
        minEdit->setPlaceholderText("Numero intero");
        maxEdit->setPlaceholderText("Numero intero");
        nameEdit->setPlaceholderText("Nome sensore");
        sensorSelector->addItem("Raggi UV");
        sensorSelector->addItem("Vento");
        sensorSelector->addItem("Umidità");

        layout->addWidget(new QLabel("Seleziona il tipo di sensore:",this),0,0);
        layout->addWidget(sensorSelector,0,1);
    }

    layout->addWidget(new QLabel("Seleziona un tipo di simulazione",this),1,0);
    layout->addWidget(modelloSelector,1,1);
    layout->addWidget(new QLabel("Inserisci un valore minimo per la simulazione:\n(entro i valori di scala del sensore)",this),3,0);
    layout->addWidget(minEdit,3,1);
    layout->addWidget(new QLabel("Inserisci un valore massimo per la simulazione:\n(entro i valori di scala del sensore)",this),4,0);
    layout->addWidget(maxEdit,4,1);
    layout->addWidget(new QLabel("Inserisci un nome:",this),5,0);
    layout->addWidget(nameEdit,5,1);
    QPushButton *okButton = new QPushButton("Accetta",this);
    layout->addWidget(okButton,6,0);
    QPushButton *annullaButton = new QPushButton("Annulla",this);
    layout->addWidget(annullaButton,6,1);


    connect(annullaButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    if(s)connect(okButton,SIGNAL(clicked(bool)),this,SLOT(collegaModifica()));
    else connect(okButton,SIGNAL(clicked(bool)),this,SLOT(collegaCrea()));
}

void createwindow::collegaModifica(){
    modelli mod =modelli{uniforme};
    if(modelloSelector->currentIndex()==0) mod=modelli{normale};
    else if(modelloSelector->currentIndex()==1) mod=modelli{costante};
    emit modifica(s,nameEdit->text(),minEdit->text().toInt(),maxEdit->text().toInt(),mod);
    qDebug()<<"Indice attuale: "<<modelloSelector->currentIndex()<<"\nModello corrispondente: "<<modelloSelector->currentText()<<"\n";
}

void createwindow::collegaCrea(){
    modelli mod =modelli{uniforme};
    if(modelloSelector->currentIndex()==0) mod=modelli{normale};
    else if(modelloSelector->currentIndex()==1) mod=modelli{costante};
    emit crea(nameEdit->text(),sensorSelector->currentIndex(),minEdit->text().toInt(),maxEdit->text().toInt(),mod);
}
