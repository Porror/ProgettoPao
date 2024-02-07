#ifndef SENSORLISTOBJ_H
#define SENSORLISTOBJ_H

#include <QWidget>
#include <QLabel>
#include <QIcon>

class SensorListObj:public QWidget
{
    Q_OBJECT
private:
    QIcon* icon;
    QLabel* iconlabel;
    QLabel* nome;
protected:
    void setIcon(const QString&);
public:
    SensorListObj(const QString&,QWidget *parent = nullptr);
    QString getName()const;
    void setNome(const QString&);
    void update();
    virtual ~SensorListObj();
};

#endif // SENSORLISTOBJ_H
