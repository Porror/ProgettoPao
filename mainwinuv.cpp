#include "mainwinuv.h"

#include "Sensor.h"

MainWinUv::MainWinUv(): graficow(new QChartView){
    mainlayout->addWidget(graficow);
    graficow->chart()->legend()->setVisible(false);
}

void MainWinUv::updateVal(const Sensor* sensore){
    //TODO connettere al controller
    data=sensore->getData();
    if(!data.empty())doGraph();
}

void MainWinUv::doGraph(){
    QChart* grafico=graficow->chart();
    grafico->removeAllSeries();
    for(auto ax:grafico->axes()) grafico->removeAxis(ax);
    //Gestione degli assi
    QValueAxis * assex = new QValueAxis;
    assex->setTitleText("Indici simulazione");
    assex->setTickCount(10);
    assex->setRange(0,data.size()-1);

    assex->setLabelFormat("%d");
    QValueAxis * assey = new QValueAxis;
    assey->setTitleText("Valori misurati indice UV");
    assey->setTickCount(10);
    {
        double min=data.front(), max=data.front();
        for(double d:data){
            if(d<min) min=d;
            if(d>max) max=d;
        }
        assey->setRange(min-1,max+1);
    }
    assey->setLabelFormat("%d");
    grafico->addAxis(assex,Qt::AlignBottom);
    grafico->addAxis(assey,Qt::AlignLeft);
    //Gestione del grafico vero e proprio
    QLineSeries * line=new QLineSeries;
    for(unsigned int i=0;i<data.size();++i){
        line->append(i,data[i]);
    }

    grafico->addSeries(line);
    line->attachAxis(assex);
    line->attachAxis(assey);

    graficow->setChart(grafico);
    graficow->update();
}
