//SPEAK C++
//BY hide-wow ON GITHUB

//MADE TO LEARN C++ / C++ SOCKETS
//USING WINSOCK

#include <winsock2.h>
#include <cstring>
#include <iostream>
#include <thread>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int clients[20];
int numClients;

void broadcast(SOCKET sock, string message)
{
    for (int client = 0; client == numClients; client++)
    {
        send(clients[numClients], message.c_str(), message.length(), 0);
    }
}

void handle(SOCKET sock)
{
    while (1)
    {
        char clientMsg[1024];
        recv(sock, clientMsg, 1024, 0);
        broadcast(sock, string(clientMsg));
    }
}

int main()
{
    // Setup var
    WSADATA WSAData;
    SOCKET sock;
    SOCKET csock;
    SOCKADDR_IN sin, csin;

    // Setup winsock
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    // Setup the socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1337);

    bind(sock, (SOCKADDR*)&sin, sizeof(sin));

    /*
    --SERVER SIDE SHEM--

    SHEM -> 
    1. Accept connexion
       |-> 2. Thread him
              |-> 3. Broadcast messages
    
    --SERVER SIDE SHEM END--
    */

    listen(sock, 0);
    while (1)
    {
        int sinsize = sizeof(csin);
        if ((csock = accept(sock, (SOCKADDR*)&csin, &sinsize)) != INVALID_SOCKET)
        {
            numClients++;
            cout << numClients << endl;
            clients[numClients] = csock;
            thread client(handle, csock);
            client.join();
        }
    }
    return 0;
}
