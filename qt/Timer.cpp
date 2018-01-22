#include "Timer.h"

Timer::Timer(QWidget *parent, int minutes, int seconds) : QLCDNumber(parent) {
    timer = new QTimer();
    timeValue = new QTime(0, minutes, seconds);

    _minutes = minutes;
    _seconds = seconds;

    this->display(timeValue->toString());
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(setDisplay()));
}

void Timer::setDisplay() {
    this->timeValue->setHMS(0,this->timeValue->addSecs(-1).minute(),this->timeValue->addSecs(-1).second());
    this->display(this->timeValue->toString());
}

void Timer::reset() {
    delete timeValue;
    timeValue = new QTime(0, _minutes, _seconds);

    this->display(timeValue->toString());
}

