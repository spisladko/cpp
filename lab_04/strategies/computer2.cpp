#include <algorithm>
#include "computer2.h"

Computer2::Computer2(std::string name) :
        name(std::move(name)) {}

Step Computer2::makeStep(const Field &fld, size_t playerNum) {
    std::vector<Cell> pieces;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Cell tmp(i, j);
            if (HelpFunctions::isFriend(fld.getCell(tmp), playerNum))
                pieces.push_back(tmp);
        }
    }

    bool mustEat = fld.canEat(playerNum);

    if (!mustEat){
        for (const auto& obj:pieces){
            if (HelpFunctions::isMan(fld.getCell(obj))){
                for (auto dx:HelpFunctions::MOVE_X){
                    int dy = HelpFunctions::MOVE_Y[playerNum];
                    Cell next(obj.x_ + dx, obj.y_ + dy);
                    if (next.isCorrect() && fld.getCell(next) == '_')
                        return {obj, next};
                }
            }

            if (HelpFunctions::isKing(fld.getCell(obj))){
                for (auto dx:HelpFunctions::MOVE_X){
                    for(auto dy:HelpFunctions::MOVE_Y){
                        Cell next(obj.x_ + dx, obj.y_ + dy);
                        if (next.isCorrect() &&
                            fld.getCell(next) == '_')
                            return {obj, next};
                    }
                }
            }
        }
        giveUp_ = true;
        return {};
    }

    if (mustEat) {
        std::vector<Step> ways;
        for (const auto& obj:pieces){
            std::vector<Step> objWays(std::move(eatProcess(fld, obj, playerNum)));
            std::move(objWays.begin(), objWays.end(), std::back_inserter(ways));
        }

        std::random_shuffle(ways.begin(), ways.end());
        size_t maxStepLengthId = 0;
        for (int i = 0; i<ways.size(); i++)
            if (ways[i].size()>ways[maxStepLengthId].size())
                maxStepLengthId = i;

        return ways[maxStepLengthId];
    }
}

std::vector<Step> Computer2::eatProcess(const Field &fld, const Cell &obj, size_t playerNum) {
    std::vector<Step> ways({Step({obj})});

    if (HelpFunctions::isMan(fld.getCell(obj))){
        for (auto dx:HelpFunctions::MOVE_X) {
            int dy = HelpFunctions::MOVE_Y[playerNum];
            Cell next(obj.x_ + dx, obj.y_ + dy);
            Cell next2(obj.x_ + 2 * dx, obj.y_ + 2 * dy);
            if (next2.isCorrect() &&
                HelpFunctions::isEnemy(fld.getCell(next), playerNum) &&
                fld.getCell(next2)=='_') {

                Field newFld(fld);
                newFld.movePiece(obj, next2, playerNum);
                for (auto&& steps:eatProcess(newFld, next2, playerNum))
                    ways.emplace_back(Step({obj})+steps);
            }
        }
    }

    if (HelpFunctions::isKing(fld.getCell(obj))){
        for (auto dx:HelpFunctions::MOVE_X){
            for(auto dy:HelpFunctions::MOVE_Y){
                Cell tmp(obj.x_ + dx, obj.y_ + dy);
                while (tmp.isCorrect()){
                    if (HelpFunctions::isFriend(fld.getCell(tmp), playerNum))
                        break;

                    if (HelpFunctions::isEnemy(fld.getCell(tmp), playerNum)){
                        tmp.x_ += dx; tmp.y_ += dy;
                        while (tmp.isCorrect() && fld.getCell(tmp) == '_'){
                            Field newFld(fld);
                            newFld.movePiece(obj, tmp, playerNum);
                            for (auto&& steps:eatProcess(newFld, tmp, playerNum))
                                ways.push_back(Step({obj}) + steps);
                            tmp.x_ += dx; tmp.y_ += dy;
                        }
                        break;
                    }
                    tmp.x_ += dx; tmp.y_ += dy;
                }
            }
        }
    }

    return ways;
}

void Computer2::printStat() const {
    std::cout << "AI model [" << name << "]: " << std::endl;
    ComputerInterface::printStat();
}
