#include "ClickableSquares.h"

ClickableSquares::ClickableSquares(int file, int rank, QWidget *parent) : QLabel(parent) {
    _x = file;
    _y = rank;

    // Find the position of the squares
    int i = (SQUARE_SIZE * file + 20);
    int j = (SQUARE_SIZE * (7-rank) + 65);
    // Draw the squares in position (i, j) of our set size
    this->setGeometry(i, j, SQUARE_SIZE, SQUARE_SIZE);
    // The background for the squares will be a complete fill
    // (we set the colors a bit later)
    this->setAutoFillBackground(true);
    // It makes everything a lot prettier if we center things
    this->setAlignment(Qt::AlignCenter);

    // So apparently there's no quick way of setting the font size...
    // so we make a copy of the font...
    QFont font = this->font();
    // ... then we set it's size...
    font.setPointSize(50);
    // ... and now we can use it
    this->setFont(font);

    // We want the squares to either have a black or white background
    if ((file + rank) % 2 == 0) {
        // Setting to black currently "hides" some of the pieces...
        // Until this is fixed, let's make it pink!
        this->setStyleSheet("QLabel {background-color : pink !important;}");

    } else {
        this->setStyleSheet("QLabel {background-color : white !important;}");
    }
}

// When a sqaures clicked, we want to get the position of the square back
void ClickableSquares::mousePressEvent(QMouseEvent *event) {
    emit clicked(_x, _y);
}
