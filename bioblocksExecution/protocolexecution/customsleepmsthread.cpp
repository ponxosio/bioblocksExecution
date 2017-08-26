#include "customsleepmsthread.h"

CustomSleepMsThread::CustomSleepMsThread(QMutex* mutex, QWaitCondition* wait, unsigned long ms2wait) {
    this->mutex = mutex;
    this->waitCondition = wait;
    this->ms2wait = ms2wait;
}

CustomSleepMsThread::~CustomSleepMsThread() {

}

void CustomSleepMsThread::run() {
    waitCondition->wait(mutex, ms2wait);
}
