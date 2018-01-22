#include "Knight.h"

Knight::Knight(int file, int rank, short colour) : Piece(file, rank, colour) {
    _isKnight = true;

    if (colour == 0) {
        _label = "\u2658";
        _labelCode = 14;

    } else {
        _label = "\u265E";
        _labelCode = 24;
    }
}