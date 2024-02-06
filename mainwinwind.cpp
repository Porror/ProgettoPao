#include "mainwinwind.h"
#include "windsensor.h"

#include<iostream>

MainWinWind::MainWinWind(): graficow(new QChartView){
    mainlayout->addWidget(graficow);
    graficow->chart()->legend()->setVisible(false);
}

void MainWinWind::updateVal(const Sensor* sensore){
    //TODO connettere al controller
    data=sensore->getData();
    if(dynamic_cast<const WindSensor*>(sensore)){
        const WindSensor* temp=dynamic_cast<const WindSensor*>(sensore);
        winddri=temp->getWindDirections();
    }
    doGraph();
    graficow->update();
}

void MainWinWind::doGraph(){
    QChart* grafico=graficow->chart();
    for(auto ax:grafico->axes()) grafico->removeAxis(ax);
    grafico->setTitle("Grafico intensità e direzione del vento (angolo rispetto al nord)");
    //Gestione degli assi
    QValueAxis *assex=new QValueAxis,*assey=new QValueAxis, *asseydir=new QValueAxis;
    assex->setTitleText("Indici simulazione");
    assex->setTickCount(10);
    assex->setRange(-1,data.size());
    assex->setLabelFormat("%d");

    assey->setTitleText("Valori intensità del vento");
    assey->setTickCount(10);
    {
        double min=data.front(),max=data.front();
        for(double d:data){
            if(d<min) min=d;
            if(d>max) max=d;
        }
        assey->setRange(min-1,max+1);
    }
    assey->setLabelFormat("%d");
    assey->setLinePen(QPen(Qt::green));

    asseydir->setTitleText("Valori intensità del vento");
    asseydir->setTickCount(10);
    asseydir->setRange(-1,365);
    asseydir->setLabelFormat("%d");
    asseydir->setLinePen(QPen(Qt::blue));

    grafico->addAxis(assex,Qt::AlignBottom);
    grafico->addAxis(assey,Qt::AlignLeft);
    grafico->addAxis(asseydir,Qt::AlignRight);

    //Gestione dei grafici
    QLineSeries * intline=new QLineSeries(grafico);
    for(unsigned int i=0;i<data.size();++i){
        intline->append(i,data[i]);
    }
    intline->setColor(Qt::green);

    QLineSeries * dirline=new QLineSeries(grafico);
    for(unsigned int i=0;i<winddri.size();++i){
        dirline->append(i,data[i]);
    }
    dirline->setColor(Qt::blue);

    grafico->addSeries(intline);
    grafico->addSeries(dirline);

    intline->attachAxis(assex);
    intline->attachAxis(assey);

    dirline->attachAxis(assex);
    dirline->attachAxis(asseydir);

    graficow->setChart(grafico);
    graficow->update();
}
