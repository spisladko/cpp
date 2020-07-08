#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <iostream>
#include "cell.h"
#include "functions.h"

class Field{
public:
    Field();
    Field(const Field& obj);
    friend std::ostream& operator<<(std::ostream& out, const Field& f);
    char getCell(const Cell& cell) const;
    int movePiece(const Cell& piece, const Cell& newCell, int playerNum);

    bool canEat(size_t playerNum) const;

private:
    char fld_[8][8];

    int moveMan(const Cell& piece1, const Cell& newCell, int playerNum);
    int moveKing(const Cell& piece1, const Cell& newCell, int playerNum);

    void setCell(const Cell& cell, char c);
};

#endif //GAME_FIELD_H