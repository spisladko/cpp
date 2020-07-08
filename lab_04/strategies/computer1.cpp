#include <algorithm>
#include <ctime>
#include "computer1.h"

Computer1::Computer1(std::string name) :
        name(std::move(name)) {}

Step Computer1::makeStep(const Field &fld, size_t playerNum) {
    std::vector<Cell> pieces;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Cell tmp(i, j);
            if (HelpFunctions::isFriend(fld.getCell(tmp), playerNum))
                pieces.push_back(tmp);
        }
    }

    std::random_shuffle(pieces.begin(), pieces.end());

    bool mustEat = fld.canEat(playerNum);
    for (const auto& obj:pieces){
        if (HelpFunctions::isMan(fld.getCell(obj))){
            for (auto dx:HelpFunctions::MOVE_X){
                int dy = HelpFunctions::MOVE_Y[playerNum];
                Cell next(obj.x_ + dx, obj.y_ + dy);
                Cell next2(obj.x_ + 2*dx, obj.y_ + 2*dy);
                if (mustEat)
                    if (next2.isCorrect() &&
                        HelpFunctions::isEnemy(fld.getCell(next), playerNum) &&
                        fld.getCell(next2) == '_')
                        return {obj, next2};
                if (!mustEat)
                    if (next.isCorrect() && fld.getCell(next) == '_')
                        return {obj, next};
            }
        }

        if (HelpFunctions::isKing(fld.getCell(obj))){
            std::vector<int> moveX(HelpFunctions::MOVE_X), moveY(HelpFunctions::MOVE_Y);
            std::random_shuffle(moveX.begin(), moveX.end());
            std::random_shuffle(moveY.begin(), moveY.end());
            for (auto dx:moveX){
                for(auto dy:moveY){
                    if (mustEat){
                        Cell tmp(obj.x_ + dx, obj.y_ + dy);
                        while (tmp.isCorrect()){
                            if (HelpFunctions::isFriend(fld.getCell(tmp), playerNum))
                                break;
                            if (HelpFunctions::isEnemy(fld.getCell(tmp), playerNum)){
                                tmp.x_ += dx; tmp.y_ += dy;
                                if (tmp.isCorrect() && fld.getCell(tmp) == '_')
                                    return {obj, tmp};
                                else
                                    break;
                            }
                            tmp.x_ += dx; tmp.y_ += dy;
                        }
                    }
                    if (!mustEat){
                        Cell next(obj.x_ + dx, obj.y_ + dy);
                        if (next.isCorrect() &&
                            fld.getCell(next)=='_')
                            return {obj, next};
                    }
                }
            }
        }
    }

    giveUp_ = true;
    return {};
}

void Computer1::printStat() const {
    std::cout << "Random model [" << name << "]: " << std::endl;
    ComputerInterface::printStat();
}
