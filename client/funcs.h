#include <iostream>
#include <string>
#include <winsock2.h>
#include <time.h>
#include <stdio.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

string RESET = "\033[0m";
string BOLD = "\033[1m";
string BLINK = "\033[5m";

string getUserName()
{
    char* user_name = getenv("USERNAME");
    return string(user_name);
}

string getTime()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%R:%S", timeinfo);
    return string(buffer);
}

void clear()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

string color(int r, int g, int b)
{
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
}

void menu()
{
    clear();
    cout << "\n         ( (\n       ) )\n     .........    Current user : [" << getUserName()
        << "]\n     | " << color(234, 73, 73) << "speak" << RESET << " |]   Time         : ["
        << getTime() << "]\n" << "     \\  " << BOLD << BLINK << color(234, 73, 73) << "c++" << RESET << "  /    Version      : [1.0]\n      `-----'\n"
        << endl;
}