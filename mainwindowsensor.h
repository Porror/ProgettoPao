#ifndef MAINWINDOWSENSOR_H
#define MAINWINDOWSENSOR_H

#include <QWidget>
#include "Observer.h"
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>

class MainWindowSensor : public QWidget,public Observer
{
    Q_OBJECT
private:
    QLabel* nome;
    QPushButton* modificaDati;
    QPushButton* simula;
protected:
    QVBoxLayout* mainlayout;
public:
    explicit MainWindowSensor(QWidget *parent = nullptr);
    void updateName(const std::string&)override;
    ~MainWindowSensor() override;
};

#endif // MAINWINDOWSENSOR_H
