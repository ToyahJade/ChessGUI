#ifndef CHESSGUI_CLICKABLESQUARES_H
#define CHESSGUI_CLICKABLESQUARES_H

#include <QLabel>

// We define the size for the squares
#define SQUARE_SIZE 70

// We make a clickable button, which is a label on steroids
// (i.e. has extra functionality)
class ClickableSquares : public QLabel {
Q_OBJECT

public:
    // This label is created with x and y coordinates
    ClickableSquares(int file, int rank, QWidget *parent =0);

signals:
    void clicked(int x, int y);

protected:
    int _x;
    int _y;

    // This overrides the default clicked signal
    // with one that emits the x and y coordinates of the label
    void mousePressEvent(QMouseEvent* event) override;

};

#endif //CHESSGUI_CLICKABLESQUARES_H
