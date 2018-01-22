#ifndef CHESS_KING_H
#define CHESS_KING_H


#include "Piece.h"

class King : public Piece {
public:
    King(int file, int rank, short colour);
    ~King() override = default;
};


#endif //CHESS_KING_H
