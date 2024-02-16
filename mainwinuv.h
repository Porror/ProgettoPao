#ifndef MAINWINUV_H
#define MAINWINUV_H

#include "mainwindowsensor.h"
#include <QtCharts>

class MainWinUv : public MainWindowSensor
{
private:
    std::vector<double> data;
    QChartView* graficow;
    void doGraph();
public:
    MainWinUv();
    ~MainWinUv();
    void updateVal(const Sensor*)override;
};

#endif // MAINWINUV_H
