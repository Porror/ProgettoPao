#include "mainwindow.h"

#include <QApplication>
#include "mainwinwind.h"
#include "windsensor.h"
#include "uvsensor.h"
#include "mainwinuv.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;

    WindSensor wind("Sensore 1",modelli{uniforme});
    wind.simulate(15);
    std::vector<double> v{5,8,4,6};
    MainWindowSensor *sensore=new MainWinWind;
    sensore->updateVal(&wind);
    w.setCentralWidget(sensore);
    std::cout<<std::rand()<<std::endl;
    w.show();
    return a.exec();
    return 0;
}
