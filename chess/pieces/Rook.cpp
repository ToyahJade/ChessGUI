#include "Rook.h"

Rook::Rook(int file, int rank, short colour) : Piece(file, rank, colour) {
    _isRook = true;

    if (colour == 0) {
        _label = "\u2656";
        _labelCode = 12;

    } else {
        _label = "\u265C";
        _labelCode = 22;
    }
}
