#include <iostream>
#include "King.h"

King::King(int file, int rank, short colour) : Piece(file, rank, colour) {
    _isKing = true;

    if (colour == 0) {
        _label = "\u2654";
        _labelCode = 10;

    } else {
        _label = "\u265A";
        _labelCode = 20;
    }
}