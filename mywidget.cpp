#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {
    // Creazione della lista e dei suoi elementi di esempio
    listWidget = new QListWidget(this);
    listWidget->addItem("Pagina 1");
    listWidget->addItem("Pagina 2");
    listWidget->addItem("Pagina 3");

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(listWidget);
    setLayout(layout);

    // Connessione del segnale doubleClicked alla nostra slot personalizzata
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MyWidget::onItemDoubleClicked);
}

void MyWidget::onItemDoubleClicked(QListWidgetItem *item) {
    // Ottenere il testo dell'elemento selezionato
    QString pagina = item->text();

    // Apri la pagina corrispondente all'elemento selezionato
    if (pagina == "Pagina 1") {
        // Apri la pagina 1
        qDebug() << "Apri pagina 1";
    } else if (pagina == "Pagina 2") {
        // Apri la pagina 2
        qDebug() << "Apri pagina 2";
    } else if (pagina == "Pagina 3") {
        // Apri la pagina 3
        qDebug() << "Apri pagina 3";
    }
}
