// ------------------ //

// ERRORS FIX IF YOU USE THE VISUAL STUDIO COMPILER
// (comment if you're using something else)

// #define _CRT_SECURE_NO_WARNINGS
// #define _WINSOCK_DEPRECATED_NO_WARNINGS

// ------------------ //

#include "funcs.h"

void sendMsg(SOCKET sock, string msg)
{
    const char* charMsg = msg.c_str();
    send(sock, msg.c_str(), strlen(charMsg), 0);
}

void handleRecv(SOCKET sock)
{
    while (true)
    {
        int recieve = 0;
        char buffer[1024] = "";

        recieve = recv(sock, buffer, 1024, 0);

        fprintf(stdout, "%.*s", recieve, buffer);
        cout << endl;
    }
}

void handleMsg(SOCKET sock)
{
    while (true)
    {
        string msg = "";
        cout << " " << username << ": ";
        getline(cin, msg);

        sendMsg(sock, msg);
    }
}

int main()
{
    // Print menu
    clear();
    string title = "Speak C++         [User : ";
    title += username;
    title += "]";
    consoleTitle(title);
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

    // Init client
    const char* passwd = "Ce4rT__(*45D-&&(fk_-jha#-$#@)(";
    char passwdResponse[1024];

    send(sock, passwd, sizeof(passwd), 0);
    recv(sock, passwdResponse, sizeof(1024), 0);

    if (passwdResponse == "NOPE")
    {
        cout << "wesh ca bug la non ?" << endl;
    }
    else if (passwdResponse == "CBON")
    {
        send(sock, username.c_str(), username.length(), 0);

        thread msghandle(handleMsg, sock);
        thread recvhandle(handleRecv, sock);
        msghandle.join();
        recvhandle.join();
    }
    else
    {
        cout << passwdResponse;
    }

    return 0;
}
