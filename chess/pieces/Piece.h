#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#define WHITE 0
#define BLACK 1

#include <string>
#include <iostream>
#include <list>

class Piece {
public:
    typedef std::list<std::pair<int,int> > positionList;

    Piece();
    Piece(int file, int rank, short colour);
    virtual ~Piece() = default;

    std::string getLabel();
    int getColour();
    int getFile();
    int getRank();
    int getLabelCode() { return _labelCode; }
    std::pair<int,int> getPosition();
    void setLabel(std::string label);
    void setColour(int colour);
    void setPosition(std::pair<int, int> position);

    bool isFirstMove() { return _isFirstMove; }

    bool isKnight() { return _isKnight; }
    bool isEmpty() { return _isEmpty; }
    bool isPawn() { return _isPawn; }
    bool isKing() { return _isKing; }
    bool isQueen() { return _isQueen; }
    bool isRook() { return _isRook; }
    bool isBishop() { return _isBishop; }

    positionList listMoves();

protected:
    std::pair<int, int> _position;
    int _colour = -1;
    std::string _label = "";
    int _labelCode = 0;

    bool _isFirstMove = true;
    bool _isQueen = false;
    bool _isRook = false;
    bool _isBishop = false;
    bool _isKnight = false;
    bool _isEmpty = false;
    bool _isKing = false;
    bool _isPawn = false;
};


#endif //CHESS_PIECE_H
