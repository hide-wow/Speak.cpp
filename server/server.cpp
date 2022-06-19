// Alot of errors and stuff i need to learn (threads lmao)
// Will fix later cause i'm alot lazy~

#include <winsock2.h>
#include <cstring>
#include <iostream>
#include <thread>
#include <list>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

class Server
{
public:
    thread threads[20];
    SOCKET clients[20];

    void clientHandle(SOCKET client)
    {
        string output;
        char buffer[1024];
        int recv_size;
        while ((recv_size = recv(client, buffer, 1024, 0)) > 0)
        {
            for (int i = 0; i < recv_size; i++)
            {
                output += buffer[i];
            }

            broadcast(output);
        }
    }

    void broadcast(string message)
    {
        for (int clientIndex = 0; clientIndex == sizeof(clients)/sizeof(*clients); clientIndex++)
        {
            if (clients[clientIndex] != INVALID_SOCKET)
            {
                send(clients[clientIndex], message.c_str(), message.length(), 0);
            }
        }
    }

    int main()
    {
        WSADATA WSAData;
        SOCKET sock;
        SOCKET csock;
        SOCKADDR_IN sin;
        SOCKADDR_IN csin;
        WSAStartup(MAKEWORD(2,0), &WSAData);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        sin.sin_addr.s_addr = INADDR_ANY;
        sin.sin_family = AF_INET;
        sin.sin_port = htons(23);
        bind(sock, (SOCKADDR *)&sin, sizeof(sin));
        listen(sock, 0);
        while(1)
        {
            int sinsize = sizeof(csin);
            if((csock = accept(sock, (SOCKADDR *)&csin, &sinsize)) != INVALID_SOCKET)
            {
                int arraySize = (sizeof(clients)/sizeof(*clients)) - 1;
                if (arraySize > 20)
                {
                    string message = "Server is full";
                    send(csock, message.c_str(), message.length(), 0);
                    closesocket(csock);
                }
                else
                {
                    clients[arraySize+1] = csock;
                    thread client (clientHandle, csock);
                }
            }
        }
        return 0;
    }

};
