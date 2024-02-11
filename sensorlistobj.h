#ifndef SENSORLISTOBJ_H
#define SENSORLISTOBJ_H

#include <QWidget>
#include <QLabel>
#include <QIcon>
#include <QPushButton>
#include "Observer.h"

class SensorListObj:public QWidget,public Observer
{
    Q_OBJECT
private:
    QIcon* icon;
    QLabel* iconlabel;
    QLabel* nome;
    QPushButton* updButton;
protected:
    void setIcon(const QString&);
public:
    SensorListObj(const QString&,QWidget *parent = nullptr);
    QString getName()const;
    void setNome(const QString&);
    void updateName(const std::string&)override;
    void updateVal(const Sensor*)override;
    void update();
    virtual ~SensorListObj();
public slots:
    void emissione();
signals:
    void click(Observer*);
};

#endif // SENSORLISTOBJ_H
