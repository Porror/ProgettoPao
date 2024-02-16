#ifndef MAINWINHUM_H
#define MAINWINHUM_H

#include "mainwindowsensor.h"
#include <QtCharts>

class MainWinHum: public MainWindowSensor
{
private:
    std::vector<double> data;
    QChartView* graficow;
    void doGraph();
public:
    MainWinHum();
    ~MainWinHum();
    void updateVal(const Sensor*)override;
};

#endif // MAINWINHUM_H
