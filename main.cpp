#include "mainwindow.h"

#include <QApplication>
#include "sensorlistuv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;

    SensorListUV sensore("Provolone");
    sensore.show();

    return a.exec();
    return 0;
}
