#include <stdexcept>
#include <vector>
#include "field.h"
#include "functions.h"

Field::Field(){
    for (int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            fld_[i][j] = '_';

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 3; j++)
            if ((i + j) % 2 == 0)
                fld_[i][j] = 'w';

    for (int i = 0; i < 8; i++)
        for (int j = 5; j < 8; j++)
            if ((i + j)%2 == 0)
                fld_[i][j] = 'b';
}

Field::Field(const Field& obj){
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            fld_[i][j] = obj.fld_[i][j];
}

std::ostream& operator<<(std::ostream& out, const Field& f){
    for (int j = 7; j >= 0; j--){
        out << j + 1;
        for (int i = 0; i < 8; i++)
            out << " " << f.fld_[i][j];
        out << "\n";
    }
    out << "  A B C D E F G H\n";
    return out;
}

char Field::getCell(const Cell& c) const{
    if (c.isCorrect())
        return fld_[c.x_][c.y_];
    throw std::out_of_range("Out of range in field");
}

void Field::setCell(const Cell& cell, char c){
    if (cell.isCorrect())
        fld_[cell.x_][cell.y_] = c;
    else
        throw std::out_of_range("Out of range in field");
}

int Field::movePiece(const Cell &piece, const Cell &newCell, int playerNum) {
    char c = getCell(piece);
    if (getCell(newCell) == '_') {
        if ((playerNum == 0 && c == 'w') ||
            (playerNum == 1 && c == 'b'))
            return moveMan(piece, newCell, playerNum);

        if ((playerNum == 0 && c == 'W') ||
            (playerNum == 1 && c == 'B'))
            return moveKing(piece, newCell, playerNum);
    }
    return -1;
}

int Field::moveMan(const Cell &piece, const Cell &newCell, int playerNum) {
    int dx = newCell.x_ - piece.x_, dy = newCell.y_ - piece.y_;
    if (dy == HelpFunctions::MOVE_Y[playerNum] && std::abs(dx)==1) {

        if (newCell.y_==HelpFunctions::KINGS_ROW[playerNum])
            setCell(newCell, HelpFunctions::KING_PIECE[playerNum]);
        else
            setCell(newCell, HelpFunctions::MAN_PIECE[playerNum]);

        setCell(piece, '_');
        return 0;
    }

    if (dy == 2*HelpFunctions::MOVE_Y[playerNum] && std::abs(dx)==2) {
        Cell enemyPiece(piece.x_+dx/2, piece.y_+dy/2);
        if (HelpFunctions::isFriend(getCell(enemyPiece), playerNum))
            return -1;
        setCell(enemyPiece, '_');
        if (newCell.y_==HelpFunctions::KINGS_ROW[playerNum])
            setCell(newCell, HelpFunctions::KING_PIECE[playerNum]);
        else
            setCell(newCell, HelpFunctions::MAN_PIECE[playerNum]);
        setCell(piece, '_');
        return 1;
    }

    return -1;
}

int Field::moveKing(const Cell &piece, const Cell &newCell, int playerNum){
    int dx = newCell.x_ - piece.x_, dy = newCell.y_ - piece.y_;
    if (std::abs(dx)!=std::abs(dy) || dx == 0)
        return -1;
    dx = (dx > 0) ? 1 : -1;
    dy = (dy > 0) ? 1 : -1;
    int enemyCount = 0;
    setCell(newCell, getCell(piece));
    setCell(piece, '_');
    for (Cell tmp = piece; tmp.x_!=newCell.x_;){
        char c = getCell(tmp);
        if (HelpFunctions::isFriend(getCell(tmp), playerNum))
            return -1;

        if (HelpFunctions::isEnemy(getCell(tmp), playerNum)) {
            enemyCount++;
            setCell(tmp, '_');
        }

        tmp.x_ += dx; tmp.y_ += dy;
    }
    if (enemyCount>1)
        return -1;
    return enemyCount;
}

bool Field::canEat(size_t playerNum) const{
    std::vector<Cell> Men;
    std::vector<Cell> Kings;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Cell c = Cell(i, j);
            if (playerNum == 0) {
                if (getCell(c) == 'w')
                    Men.push_back(c);
                if (getCell(c) == 'W')
                    Kings.push_back(c);
            }
            if (playerNum == 1) {
                if (getCell(c) == 'b')
                    Men.push_back(c);
                if (getCell(c) == 'B')
                    Kings.push_back(c);
            }
        }
    }

    for (const auto& cell:Men){
        for (auto dx:HelpFunctions::MOVE_X){
            int dy = HelpFunctions::MOVE_Y[playerNum];
            Cell enemyCell(cell.x_ + dx, cell.y_ + dy);
            Cell emptyCell(cell.x_ + 2*dx, cell.y_ + 2*dy);
            if (emptyCell.isCorrect() &&
                HelpFunctions::isEnemy(getCell(enemyCell), playerNum) &&
                getCell(emptyCell) == '_')
                return true;
        }
    }

    for (const auto& cell:Kings){
        for (auto dx:HelpFunctions::MOVE_X){
            for (auto dy:HelpFunctions::MOVE_Y){
                Cell tmp(cell.x_ + dx, cell.y_ + dy);
                while(tmp.isCorrect()){
                    if (HelpFunctions::isFriend(getCell(tmp), playerNum))
                        break;
                    if (HelpFunctions::isEnemy(getCell(tmp), playerNum)){
                        tmp.x_ += dx; tmp.y_ += dy;
                        if (tmp.isCorrect() && getCell(tmp) == '_')
                            return true;
                        break;
                    }
                    tmp.x_ += dx; tmp.y_ += dy;
                }
            }
        }
    }

    return false;
}