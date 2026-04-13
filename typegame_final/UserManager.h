#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "common.h"
using namespace std;
class UserManager
{
private:
    user users[MAX_User];
    int userCount;

public:
    UserManager();
    void loadUsers();    // 读
    void saveUsers();    // 存
    bool registerUser(); // 注册
    bool login(string &loggedUsername);
};

#endif