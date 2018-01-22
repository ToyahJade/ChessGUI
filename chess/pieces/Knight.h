#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "Piece.h"

class Knight : public Piece {
public:
    Knight(int file, int rank, short colour);
    ~Knight() override = default;
};


#endif //CHESS_KNIGHT_H
