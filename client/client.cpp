#include "funcs.h"

// ------------------ //

//* ERRORS FIX IF YOU USE THE VISUAL STUDIO COMPILER *//
// (comment if you're using something else)

// #define _CRT_SECURE_NO_WARNINGS
// #define _WINSOCK_DEPRECATED_NO_WARNINGS

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

// ------------------ //

void sendMsg(SOCKET sock, string msg)
{
    const char* rMsg = msg.c_str();
    send(sock, rMsg, msg.length(), 0);
}

void handleMsg(SOCKET sock)
{
    while (true)
    {
        // Client side msg part:
        string msg;
        char buffer[1024];
        int recieve;
        cout << " " << getUserName() << ": ";
        getline(cin, msg);

        sendMsg(sock, msg);

        // Recieve part
        recieve = recv(sock, buffer, 1024, 0);
        fprintf(stdout, "%.*s", recieve, buffer);
        cout << endl;
    }
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
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_addr.s_addr = inet_addr(ip.c_str());
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    // Connect & test
    connect(sock, (SOCKADDR*)&sin, sizeof(sin));

    handleMsg(sock);

    closesocket(sock);
    WSACleanup();

    return 0;
}