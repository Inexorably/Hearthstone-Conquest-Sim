#include "simthread.h"
#include "globals.h"
#include "sim.h"
#include <QtCore>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QProgressBar"
#include "globals.h"

#include <QDebug>

extern bool singleElim;
extern bool doubleElim;

simThread::simThread(){

}
/*
void simThread::percentChanged(int num){
    return;
}*/

void simThread::run(){
    //The current progress, varies [0 100].
    //int prog = 0;
    for (int g = 0; g < numSims; g++){
        //Avoid crashing.
        QMutex mutex;
        mutex.lock();
        if (this->stop)
            break;
        mutex.unlock();

        if (!singleElim && !doubleElim)
            runSimulation();
        else if (singleElim)
            runSingle();
        else if (doubleElim)
            runDouble();


        //Debug()() << "g: " << g << " || numSims: " << numSims << " || g/numSims: " << g*100/numSims << " || Prog: " << prog;

        //We update the progress bar if we need to.
        //if (g*100/numSims > prog){
            //Debug()() << "In if statement.";
            //prog = 100*g/numSims;
            emit percentChanged(g);
        //}
    }
    orderResults();
    emit percentChanged(numSims);

    //We will update the results to the table now.
    emit runComplete(1);

}
