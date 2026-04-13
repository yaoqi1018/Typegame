#include "UserManager.h"
#include <iostream>
#include <fstream>

using namespace std;

UserManager::UserManager() : userCount(0) {}

void UserManager::loadUsers()
{
    ifstream fin("users.txt");
    if (!fin.is_open())
        return;
    userCount = 0;
    while (fin >> users[userCount].username >> users[userCount].password)
    {
        userCount++;
        if (userCount >= MAX_User)
            break;
    }
    fin.close();
}

void UserManager::saveUsers()
{
    ofstream fout("users.txt");
    if (!fout.is_open())
        return;
    for (int i = 0; i < userCount; ++i)
    {
        fout << users[i].username << " " << users[i].password << endl;
    }
    fout.close();
}

bool UserManager::registerUser()
{
    string username, password;
    cout << "请输入用户名" << endl;
    cin >> username;
    for (int i = 0; i < userCount; ++i)
    {
        if (users[i].username == username)
        {
            cout << "用户名已存在" << endl;
            return false;
        }
    }
    cout << "请输入密码" << endl;
    cin >> password;
    users[userCount].username = username;
    users[userCount].password = password;
    userCount++;
    cout << "已成功注册" << endl;
    return true;
}

bool UserManager::login(string &loggedUsername)
{
    string username, password;
    cout << "请输入用户名" << endl;
    cin >> username;
    cout << "请输入密码" << endl;
    cin >> password;
    for (int i = 0; i < userCount; ++i)
    {
        if (users[i].username == username && users[i].password == password)
        {
            cout << "登录成功" << endl;
            cout << "欢迎 " << username << endl;
            loggedUsername = username;
            return true;
        }
    }
    cout << "用户名或密码错误" << endl;
    return false;
}