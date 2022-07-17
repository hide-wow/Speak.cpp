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

string passwd = "Ce4rT__(*45D-&&(fk_-jha#-$#@)(";

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
        int recieve = 0;
        char clientMsg[1024] = "";

        recieve = recv(sock, clientMsg, 1024, 0);
        fprintf(stdout, "%.*s", recieve, clientMsg);

        if (clientMsg == "EXIT")
        {
            break;
        }
        else
        {
            broadcast(sock, string(clientMsg));
        }
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
            char passwdClient[1024] = "";
            recv(sock, passwdClient, 1024, 0);

            if (passwdClient == passwd)
            {
                send(csock, "CBON", 4, 0);
                numClients++;
                cout << numClients << endl;
                clients[numClients] = csock;
                thread client(handle, csock);
                client.join();
            }

            else
            {
                send(csock, "NOPE", 4, 0);
                closesocket(csock);
            }
        }
    }
    return 0;
}
