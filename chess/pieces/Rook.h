#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include <iostream>
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(int file, int rank, short colour);
    ~Rook() override = default;
};


#endif //CHESS_ROOK_H
