#include <iostream>
#include "Bishop.h"

Bishop::Bishop(int file, int rank, short colour) : Piece(file, rank, colour) {
    _isBishop = true;

    if (colour == 0) {
        _label = "\u2657";
        _labelCode = 13;

    } else {
        _label = "\u265D";
        _labelCode = 23;
    }
}
