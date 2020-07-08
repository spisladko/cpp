#include "functions.h"

bool HelpFunctions::isMan(char c) {
    return (c == 'w' || c == 'b');
}

bool HelpFunctions::isKing(char c) {
    return (c == 'W' || c == 'B');
}

bool HelpFunctions::isBlack(char c){
    return (c == 'b' || c == 'B');
}

bool HelpFunctions::isWhite(char c){
    return (c == 'w' || c == 'W');
}

bool HelpFunctions::isFriend(char c, size_t playerNum) {
    if (playerNum == 0 && isWhite(c))
        return true;
    if (playerNum == 1 && isBlack(c))
        return true;
    return false;
}

bool HelpFunctions::isEnemy(char c, size_t playerNum) {
    if (playerNum == 0 && isBlack(c))
        return true;
    if (playerNum == 1 && isWhite(c))
        return true;
    return false;
}