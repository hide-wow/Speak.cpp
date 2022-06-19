#include <iostream>
#include <string>
#include <winsock2.h>
#include <time.h>
#include <stdio.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

// ------------------ //

//* ERRORS FIX IF YOU USE THE VISUAL STUDIO COMPILER *//
// (comment if you're using something else)

// #define _CRT_SECURE_NO_WARNINGS
// #define _WINSOCK_DEPRECATED_NO_WARNINGS

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

// ------------------ //

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

void sendMsg(SOCKET sock, string msg)
{
    auto rMsg = msg.c_str();
    send(sock, rMsg, sizeof(rMsg), 0);
}

void handleMsg(SOCKET sock, char* buffer)
{
    // Client side msg part:
    string msg;
    int recieve;
    cout << " " << getUserName() << ": ";
    getline(cin, msg);

    sendMsg(sock, msg);

    // Recieve part
    recieve = recv(sock, buffer, 1024, 0);
    fprintf(stdout, "%.*s", recieve, buffer);
    cout << endl;
}

int main()
{
    // Print menu
    clear();
    SetConsoleTitleA("Speak C++");
    menu();

    // Setup vars and ip / port
    string ip;
    int port;
    cout << " server ip: ";
    cin >> ip;
    cout << " server port: ";
    cin >> port;
    cout << endl;

    // Init winsock
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[1024];
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_addr.s_addr = inet_addr(ip.c_str());
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    // Connect & test
    connect(sock, (SOCKADDR*)&sin, sizeof(sin));

    while (true)
    {
        handleMsg(sock, buffer);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}
