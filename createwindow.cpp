#include "createwindow.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QIntValidator>

#include "uvsensor.h"
#include "humiditysensor.h"
#include "windsensor.h"

createwindow::~createwindow(){
    if(s) delete s;//al resto pensa qt quando chiudo la finestra
}

createwindow::createwindow(Sensor* sen,QWidget*parent):QWidget{parent},s(sen),minEdit(new QLineEdit(this))
    ,maxEdit(new QLineEdit(this)),nameEdit(new QLineEdit(this)),modelloSelector(new QComboBox(this)),
    minimo(new QLabel("Inserisci un valore di minimo:",this)),sensorSelector(new QComboBox(this)){

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
    layout->addWidget(minimo,3,0);
    modificarange(0);//per inserire il testo corretto
    layout->addWidget(minEdit,3,1);
    layout->addWidget(new QLabel("Inserisci un valore massimo:",this),4,0);
    layout->addWidget(maxEdit,4,1);
    layout->addWidget(new QLabel("Inserisci un nome:",this),5,0);
    layout->addWidget(nameEdit,5,1);
    QPushButton *okButton = new QPushButton("Accetta",this);
    layout->addWidget(okButton,6,0);
    QPushButton *annullaButton = new QPushButton("Annulla",this);
    layout->addWidget(annullaButton,6,1);


    connect(annullaButton,SIGNAL(clicked(bool)),this,SLOT(close()));//bottone annulla chiudi finestra
    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(close()));//bottone ok chiudi finestra
    if(s)connect(okButton,SIGNAL(clicked(bool)),this,SLOT(collegaModifica()));//bottone ok signal
    else connect(okButton,SIGNAL(clicked(bool)),this,SLOT(collegaCrea()));//bottone ok signal
    connect(sensorSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(modificarange(int)));//selector modificarange
}

void createwindow::collegaModifica(){
    modelli mod =modelli{uniforme};
    if(modelloSelector->currentIndex()==0) mod=modelli{normale};
    else if(modelloSelector->currentIndex()==1) mod=modelli{costante};
    emit modifica(s,nameEdit->text(),minEdit->text().toInt(),maxEdit->text().toInt(),mod);
}

void createwindow::collegaCrea(){
    modelli mod =modelli{uniforme};
    if(modelloSelector->currentIndex()==0) mod=modelli{normale};
    else if(modelloSelector->currentIndex()==1) mod=modelli{costante};
    emit crea(nameEdit->text(),sensorSelector->currentIndex(),minEdit->text().toInt(),maxEdit->text().toInt(),mod);
}

void createwindow::modificarange(int sel){
    QString supp="";
    if(0==sel){//UVSensor
        supp="Inserisci un valore minimo:\nValori ammessi tra ";
        supp.append(QString::number(UVSensor::getMinscale()));
        supp.append(" e ");
        supp.append(QString::number(UVSensor::getMaxscale()));
    }
    else if(1==sel){//WindSensor
        supp="Inserisci un valore minimo:\nValori ammessi tra ";
        supp.append(QString::number(WindSensor::getMinscale()));
        supp.append(" e ");
        supp.append(QString::number(WindSensor::getMaxscale()));
    }
    else if(2==sel){//HumiditySensor
        supp="Inserisci un valore minimo:\nValori ammessi tra ";
        supp.append(QString::number(HumiditySensor::getMinscale()));
        supp.append(" e ");
        supp.append(QString::number(HumiditySensor::getMaxscale()));
    }
    minimo->setText(supp);
    minimo->update();
}
