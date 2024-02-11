#include <QApplication>
#include <QInputDialog>
#include <QDebug>


#include <QtWidgets>
#include "controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow *w =new MainWindow();
    controller c(new ConcreteSaver(),w);
    w->show();
    return app.exec();
}
