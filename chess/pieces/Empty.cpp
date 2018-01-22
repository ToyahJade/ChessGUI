#include "Empty.h"

Empty::Empty(int file, int rank) : Piece(file, rank, -1) {
    _colour = -1;
    _label = "";
    _isEmpty = true;
}