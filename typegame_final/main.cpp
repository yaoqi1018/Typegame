#include "Game.h"

using namespace std;

int main()
{
    UserManager userMgr;
    HistoryManager historyMgr;
    Game game(userMgr, historyMgr);
    game.run();

    return 0;
}