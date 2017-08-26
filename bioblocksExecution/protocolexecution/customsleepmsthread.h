#ifndef CUSTOMSLEEPMSTHREAD_H
#define CUSTOMSLEEPMSTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class CustomSleepMsThread : public QThread
{
       Q_OBJECT
public:
    CustomSleepMsThread(QMutex* mutex, QWaitCondition* waitCondition, unsigned long ms2wait);
    virtual ~CustomSleepMsThread();

protected:
    QMutex* mutex;
    QWaitCondition* waitCondition;
    unsigned long ms2wait;

    void run();
};

#endif // CUSTOMSLEEPMSTHREAD_H
