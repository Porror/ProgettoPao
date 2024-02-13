#ifndef MAINWINDOWSENSOR_H
#define MAINWINDOWSENSOR_H

#include <QWidget>
#include "Observer.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>

class MainWindowSensor : public QWidget,public Observer
{
    Q_OBJECT
private:
    QLabel* nome;
    QPushButton* modificaDati;
    QPushButton* simula;
    QLineEdit* numsim;
protected:
    QGridLayout* mainlayout;
private slots:
    void slotModifica();
    void slotSimula();
public:
    explicit MainWindowSensor(QWidget *parent = nullptr);
    void updateName(const std::string&)override;
    ~MainWindowSensor() override;
    void setName(const QString&);
signals:
    void modificaPremuta();
    void simulaPreuta(unsigned int);
};

#endif // MAINWINDOWSENSOR_H
