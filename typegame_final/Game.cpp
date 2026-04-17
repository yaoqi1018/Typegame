#include "Game.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib> //
#include <algorithm>
#include <iomanip>
#include <conio.h>   //
#include <windows.h> // 用于控制台颜色

#define GREEN 10
#define RED 12
#define WHITE 7

using namespace std;

Game::Game(UserManager &um, HistoryManager &hm) : userMgr(um), historyMgr(hm) {}
// 用于测试
void Game::loadQuestions(const string &filename, vector<string> &container)
{
    ifstream fin(filename);
    string line;
    while (getline(fin, line))
    {
        if (!line.empty())
            container.push_back(line);
    }
    fin.close();
}

string Game::getText(int dif)
{
    if (dif == 1 && !easyQuestions.empty())
        return easyQuestions[rand() % easyQuestions.size()];
    else if (dif == 2 && !mediumQuestions.empty())
        return mediumQuestions[rand() % mediumQuestions.size()];
    else if (dif == 3 && !hardQuestions.empty())
        return hardQuestions[rand() % hardQuestions.size()];
    else
        return "No question available. Please check your text files.";
}

void Game::cleanInput()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

void Game::start(const string &username)
{
    cout << "请选择难度" << endl;
    cout << "1.简单" << endl;
    cout << "2.中等" << endl;
    cout << "3.困难" << endl;
    int dif;
    cin >> dif;
    if (dif < 1 || dif > 3)
    {
        cout << "选择无效" << endl;
        return;
    }
    cleanInput();

    string sentence = getText(dif);
    cout << sentence << endl;
    cout << "按下回车开始练习" << endl;

    while (cin.get() != '\n')
        ; // 等待回车

    clock_t startTime = clock();
    cout << "请输入以上文本，注意标点与大小写" << endl;
    string userInput;
    int pos = 0;
    int len = sentence.size();
    int cor = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (pos < len)
    {
        char ch = _getch();
        if (ch == '\r')
            break;                // 按回车提前结束
        if (ch == 8 || ch == 127) // 退格键 (8 for Windows, 127 for Unix)
        {
            if (pos > 0)
            {
                pos--;
                if (userInput.back() == sentence[pos])
                    cor--;
                userInput.pop_back();
                cout << "\b \b"; // 回退并清除字符
            }
            continue;
        }
        if (ch == sentence[pos])
        {
            SetConsoleTextAttribute(hConsole, GREEN); // 绿色
            cor++;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, RED); // 红色
        }
        cout << ch;
        SetConsoleTextAttribute(hConsole, WHITE); // 恢复默认白色
        userInput.push_back(ch);
        pos++;
    }
    clock_t endTime = clock();
    double ela = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    double ac = cor * 100.0 / len;
    double speed = cor / (ela / 60.0);
    cout << endl;
    cout << "正确字符数:" << cor << "/" << len << endl;
    cout << "正确率：" << fixed << setprecision(2) << ac << "%" << endl;
    cout << "用时：" << fixed << endl
         << setprecision(2) << ela << "s" << endl;
    cout << "速度：" << speed << "字/分钟" << endl;
    cout << "按回车键继续" << endl;
    historyMgr.addRecord(username, time(nullptr), dif, ac, speed);
}

void Game::showMenu(const string &loggedUser)
{
    int choice;

    while (true)
    {
        cout << "1.开始练习" << endl;
        cout << "2.查看历史记录" << endl;
        cout << "3.注销当前用户" << endl;
        cout << "请输入选择" << endl;
        cin >> choice;
        if (cin.fail())
        {
            cleanInput();
            cout << "请正确输入！" << endl;
            continue;
        }
        if (choice)
            switch (choice)
            {
            case 1:
                start(loggedUser);
                break;
            case 2:
                historyMgr.showHistory(loggedUser);
                break;
            case 3:
                cout << "已注销" << endl;
                return;
            default:
                cout << "请重新进行有效选择" << endl;
            }
    }
}

void Game::run()
{
    // 初始化随机数种子
    srand((unsigned int)time(NULL));

    // 加载数据
    userMgr.loadUsers();
    historyMgr.loadHistories();
    loadQuestions("easy.txt", easyQuestions);
    loadQuestions("medium.txt", mediumQuestions);
    loadQuestions("hard.txt", hardQuestions);

    int choice;
    string loggedUser;
    while (true)
    {
        cout << "=====TypeGame=====" << endl;
        cout << "1.登录已有账号" << endl;
        cout << "2.注册新用户" << endl;
        cout << "3.退出" << endl;
        cout << "注意！正确退出才可保存数据！" << endl;
        cin >> choice;
        if (cin.fail())
        {
            cleanInput();
            cout << "请正确输入！" << endl;
            continue;
        }
        switch (choice)
        {
        case 1:
            if (userMgr.login(loggedUser))
            {
                showMenu(loggedUser);
            }
            break;
        case 2:
            userMgr.registerUser();
            break;
        case 3:
            cout << "正在保存数据并退出" << endl;
            userMgr.saveUsers();
            historyMgr.saveHistories();
            return;
        default:
            cout << "请输入正确的选择" << endl;
        }
    }
}
