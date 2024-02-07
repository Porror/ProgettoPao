#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sensorlistobj.h"
#include <QHBoxLayout>
#include "mainwindowsensor.h"


class MainWindow : public QMainWindow

{
    Q_OBJECT

private:
    std::list<SensorListObj*> sensori; //lista dei sensori contenuti nella mainwinvdow
    QHBoxLayout* mainlayout;
    MainWindowSensor * sensor; //sensore contenuto nella parte principale della finestra
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void search(const QString& nome);
};

#endif // MAINWINDOW_H
