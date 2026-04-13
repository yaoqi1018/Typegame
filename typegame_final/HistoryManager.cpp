#include "HistoryManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

HistoryManager::HistoryManager() : historyCount(0) {}

void HistoryManager::loadHistories()
{
    ifstream fin("history.txt");
    if (!fin.is_open())
        return;
    historyCount = 0;
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string username;
        long long t_ll;
        int dif;
        double ac, speed;
        if (ss >> username >> t_ll >> dif >> ac >> speed)
        {
            histories[historyCount].username = username;
            histories[historyCount].time = (time_t)t_ll;
            histories[historyCount].dif = dif;
            histories[historyCount].ac = ac;
            histories[historyCount].speed = speed;
            historyCount++;
            if (historyCount >= MAX_History)
                break;
        }
    }
    fin.close();
}

void HistoryManager::saveHistories()
{
    ofstream fout("history.txt");
    if (!fout.is_open())
        return;
    for (int i = 0; i < historyCount; ++i)
    {
        fout << histories[i].username << " "
             << (long long)histories[i].time << " "
             << histories[i].dif << " "
             << fixed << setprecision(2) << histories[i].ac << " "
             << histories[i].speed << endl;
    }
    fout.close();
}

void HistoryManager::addRecord(const string &username, time_t t, int dif, double ac, double speed)
{
    if (historyCount >= MAX_History)
    {
        cout << "历史记录已满，无法保存新记录" << endl;
        return;
    }
    histories[historyCount].username = username;
    histories[historyCount].time = t;
    histories[historyCount].dif = dif;
    histories[historyCount].ac = ac;
    histories[historyCount].speed = speed;
    historyCount++;
}

void HistoryManager::showHistory(const string &username)
{
    cout << "历史记录" << endl;
    bool found = false;
    for (int i = 0; i < historyCount; ++i)
    {
        if (histories[i].username == username)
        {
            found = true;
            stringstream ss;
            ss << put_time(localtime(&histories[i].time), "%Y-%m-%d %H:%M:%S");
            cout << "|时间：" << ss.str() << "|" << endl;
            cout << "|难度：";
            if (histories[i].dif == 1)
                cout << "简单";
            else if (histories[i].dif == 2)
                cout << "中等";
            else
                cout << "困难";
            cout << "|正确率：" << fixed << setprecision(2) << histories[i].ac << "%";
            cout << "|速度：" << fixed << setprecision(2) << histories[i].speed << "字/分钟|" << endl;
        }
    }
    if (!found)
    {
        cout << "暂无记录" << endl;
        cout << "按回车键继续" << endl;
    }
    cin.ignore();
    cin.get();
}