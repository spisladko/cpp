#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <vector>

namespace HelpFunctions {
    const std::vector<char> MAN_PIECE({'w', 'b'});
    const std::vector<char> KING_PIECE({'W', 'B'});

    const std::vector<int> MOVE_Y({1, -1});
    const std::vector<int> MOVE_X({1, -1});

    const std::vector<int> KINGS_ROW({7, 0});

    bool isMan(char c);
    bool isKing(char c);
    bool isBlack(char c);
    bool isWhite(char c);
    bool isFriend(char c, size_t playerNum);
    bool isEnemy(char c, size_t playerNum);
}

#endif //GAME_FUNCTIONS_H
