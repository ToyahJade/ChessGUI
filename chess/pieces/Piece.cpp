#include <iostream>
#include <cmath>
#include "Piece.h"

Piece::Piece(int file, int rank, short colour) {
    _position = std::make_pair(file, rank);
    _colour = colour;
}

std::string Piece::getLabel() {
    return _label;
}

void Piece::setLabel(std::string label) {
    _label = label;
}

int Piece::getColour() {
    return _colour;
}

int Piece::getFile() {
    return _position.first;
}

int Piece::getRank() {
    return _position.second;
}

std::pair<int, int> Piece::getPosition() {
    return _position;
}

void Piece::setPosition(std::pair<int, int> position) {
    _position = position;
    _isFirstMove = false;
}

Piece::positionList Piece::listMoves() {
    Piece::positionList tempList = {};

    if (isKing()) {
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if ((i == 0) && (j == 0)) continue;

                int temp_x = i + _position.first;
                int temp_y = j + _position.second;

                if ((temp_x >= 0) && (temp_x < 8) && (temp_y >= 0) && (temp_y < 8)) {
                    tempList.emplace_back(temp_x, temp_y);
                }
            }
        }

    } else if (isKnight()) {
        int move_x[] = {1, 2, 2, 1, -1, -2, -2, -1};
        int move_y[] = {2, 1, -1, -2, -2, -1, 1, 2};

        int temp_x = 0;
        int temp_y = 0;
        for (int i = 0; i < 8; ++i) {
            temp_x = _position.first + move_x[i];
            temp_y = _position.second + move_y[i];

            if ((temp_x >= 0) && (temp_x < 8) && (temp_y >= 0) && (temp_y < 8)) {
                tempList.emplace_back(temp_x, temp_y);
            }
        }

    } else if (isPawn()) {
        int direction = pow(-1, double(_colour));

        for (int i = -1; i < 2; ++i) {
            if ((_position.second + direction >= 0) &&
                (_position.second + direction < 8) &&
                (_position.first + i >= 0) &&
                (_position.first + i < 8)) {
                tempList.emplace_back(_position.first + i, _position.second + direction);
            }
        }

        if (_isFirstMove && (_position.second + 2*direction >= 0) && (_position.second + 2*direction < 8)) {
            tempList.emplace_back(_position.first, _position.second + 2*direction);
        }
    }

    if (isBishop() || isQueen()) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if ((i == _position.first) && (j == _position.second)) continue;

                if (abs(i - _position.first) == abs(j - _position.second)) {
                    tempList.emplace_back(i, j);
                }
            }
        }
    }

    if (isRook() || isQueen()) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if ((i == _position.first) && (j == _position.second)) continue;

                if ((i == _position.first) || (j == _position.second)) {
                    tempList.emplace_back(i, j);
                }
            }
        }
    }

    return tempList;
}

void Piece::setColour(int colour) {
    _colour = colour;
}

Piece::Piece() = default;
