#ifndef SIMTHREAD_H
#define SIMTHREAD_H

#include <QtCore>

class simThread :public QThread{
    Q_OBJECT

    public:
        simThread();
        void run();
        int numSims;
        bool stop;
    signals:
        void percentChanged(int);
        void runComplete(int);
};

#endif // SIMTHREAD_H
