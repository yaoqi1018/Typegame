#ifndef GAME_H
#define GAME_H

#include "UserManager.h"
#include "HistoryManager.h"
#include <vector>
#include <string>

using namespace std;

class Game
{
private:
    UserManager &userMgr;
    HistoryManager &historyMgr;
    vector<string> easyQuestions;
    vector<string> mediumQuestions;
    vector<string> hardQuestions;

    void loadQuestions(const string &filename, vector<string> &container);
    string getText(int dif);
    void cleanInput();
    void start(const string &username);
    void showMenu(const string &loggedUser);

public:
    Game(UserManager &um, HistoryManager &hm);
    void run();
};

#endif