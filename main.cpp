#include <QApplication>
#include <QInputDialog>
#include <QDebug>


#include <QtWidgets>
#include "presenter.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow *w =new MainWindow();
    presenter c(new ConcreteSaver(),w);
    w->show();
    return app.exec();
}
