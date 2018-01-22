#ifndef CHESSGUI_TIMER_H
#define CHESSGUI_TIMER_H


#include <QtWidgets/QLCDNumber>
#include <QTime>
#include <QTimer>


class Timer : public QLCDNumber {
Q_OBJECT

public:
    Timer(QWidget *parent, int minutes, int seconds);

    QTimer* timer;
    QTime* timeValue;

    void reset();

private:
    int _minutes;
    int _seconds;

public slots:
    void setDisplay();
};


#endif //CHESSGUI_TIMER_H
