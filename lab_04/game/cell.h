#ifndef GAME_CELL_H
#define GAME_CELL_H


class Cell {
public:
    Cell(int x, int y);
    bool isCorrect() const;

    int x_, y_;
};


#endif //GAME_CELL_H
