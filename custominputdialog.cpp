#include "custominputdialog.h"

CustomInputDialog::CustomInputDialog(int min,int max,QString nome,QWidget * parent):QDialog(parent),
    minEdit(new QLineEdit),maxEdit(new QLineEdit),nameEdit(new QLineEdit){

    minEdit->setText(QString::number(min));
    minEdit->setClearButtonEnabled(true);
    maxEdit->setText(QString::number(max));
    maxEdit->setClearButtonEnabled(true);
    nameEdit->setText(nome);
    nameEdit->setClearButtonEnabled(true);

    setupUI();
}

CustomInputDialog::~CustomInputDialog(){
    this->close();
}

CustomInputDialog::InputData CustomInputDialog::getValues() const{
    InputData values;
    values.min=minEdit->text().toInt();
    values.max=maxEdit->text().toInt();
    values.name=nameEdit->text();
    return values;
}

void CustomInputDialog::setupUI(){
    QGridLayout *layout = new QGridLayout(this);

    // Campo per l'inserimento del minimo
    minEdit->setValidator(new QIntValidator(this));
    layout->addWidget(new QLabel("Inserisci un valore minimo:"),0,0);
    layout->addWidget(minEdit,0,1);

    maxEdit->setValidator(new QIntValidator(this));
    layout->addWidget(new QLabel("inserisci un valore massimo:"),1,0);
    layout->addWidget(maxEdit,1,1);

    // Campo per l'inserimento del testo
    layout->addWidget(new QLabel("inserisci un nome:", this),2,0);
    layout->addWidget(nameEdit,2,1);

    // Bottone di conferma
    QPushButton *okButton = new QPushButton("OK", this);
    layout->addWidget(okButton);

    setLayout(layout);
    setWindowTitle("Modifica dati sensore");

    connect(okButton, &QPushButton::clicked, this, &CustomInputDialog::accept);
}
