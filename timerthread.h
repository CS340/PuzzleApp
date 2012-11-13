#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>

class TimerThread : public QThread
{

    Q_OBJECT

private:
    void run();

};

#endif // TIMERTHREAD_H
