#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include "common.h"
#include <string>

class HistoryManager
{
private:
    History histories[MAX_History];
    int historyCount;

public:
    HistoryManager();
    void loadHistories();                                                               // 读之前的记录
    void saveHistories();                                                               // 保存记录
    void addRecord(const string &username, time_t t, int dif, double ac, double speed); // 添加记录
    void showHistory(const string &username);                                           // 打印记录
};

#endif