#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <ctime>

using namespace std;

const int MAX_User = 100;
const int MAX_History = 500;

struct user
{
    string username;
    string password;
};

struct History
{
    string username;
    time_t time;
    int dif;
    double ac;
    double speed;
};

#endif