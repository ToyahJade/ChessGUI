#include <iostream>
#include "Queen.h"

Queen::Queen(int file, int rank, short colour) : Piece(file, rank, colour) {
    _isQueen = true;

    if (colour == 0) {
        _label = "\u2655";
        _labelCode = 11;

    } else {
        _label = "\u265B";
        _labelCode = 21;
    }
}


