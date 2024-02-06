#ifndef MAINWINWIND_H
#define MAINWINWIND_H

#include "mainwindowsensor.h"
#include <QtCharts>

class MainWinWind : public MainWindowSensor
{
private:
    std::vector<double> data;
    std::vector<unsigned int> winddri;
    QChartView* graficow;
    void doGraph();
public:
    MainWinWind();
    void updateVal(const Sensor*)override;
};

#endif // MAINWINWIND_H
