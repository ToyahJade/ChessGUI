#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H


#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(int file, int rank, short colour);
    ~Bishop() override = default;
};


#endif //CHESS_BISHOP_H
