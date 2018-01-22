#include <cmath>
#include "Pawn.h"

Pawn::Pawn(int file, int rank, short colour) : Piece(file, rank, colour) {
    _isPawn = true;

    if (colour == 0) {
        _label = "\u2659";
        _labelCode = 15;

    } else {
        _label = "\u265F";
        _labelCode = 25;
    }
}