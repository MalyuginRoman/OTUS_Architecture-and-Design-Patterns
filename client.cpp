#include <iostream>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inaddr.h>
#include <stdio.h>
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <vector>
#include "imessage.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

vector <char> convert(vector <char> result, string s)
{
    size_t l = s.length();
    for(int i = l - 1; i > -1; i--)
        result.emplace(result.begin(), s.at(i));
    return result;
}

int main(void)
{
    const char SERVER_IP[] = "10.124.40.14";
    const short SERVER_PORT_NUM = 615;
    const short BUFF_SIZE = 1024;

    int erStat;
    in_addr ip_to_num;
    inet_pton(AF_INET, SERVER_IP, &ip_to_num);

    WSADATA wsData;
    erStat = WSAStartup(MAKEWORD(2,2), &wsData);

#ifdef _WIN32
    if (erStat != 0)
    {
        cout << "Error WinSock version initializaion #";
        cout << WSAGetLastError();
        return 1;
    }
    else
        cout << "WinSock initialization is OK" << endl;
    SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);
    if (ClientSock == INVALID_SOCKET)
    {
        cout << "Error initialization socket # " << WSAGetLastError() << endl;
        closesocket(ClientSock);
        WSACleanup();
    }
    else
        cout << "Client socket initialization is OK" << endl;

    sockaddr_in servInfo;
    ZeroMemory(&servInfo, sizeof(servInfo));
#else
    int ServSock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servInfo;
    memset(&servInfo, '0', sizeof(servInfo));
#endif
    
    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(SERVER_PORT_NUM);

#ifdef _WIN32
    erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));
    if (erStat != 0)
    {
        cout << "Connection to Server is FAILED. Error # " << WSAGetLastError() << endl;
        closesocket(ClientSock);
        WSACleanup();
        return 1;
    }
    else
        cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" << endl;
#else
    if(connect(ClientSock, (struct sockaddr *)&servInfo, sizeof(servInfo))<0)
    {
        cout << "Connection failed due to port and ip problems " << endl;
        return 1;
    }
#endif

    vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
    short packet_size = 0;

    while (true)
    {
        cout << "Your (Client) message to Server: ";

// формирование клиентского пакета
//-----------------------------------------------------------------------------------------
        Builder* b1 = new Builder;
        b1->setGameId("1");
        b1->setObjectId("1");
        b1->setOperationId("1");
        b1->setArgs("vector.at(0)");

        clientBuff = convert(clientBuff, b1->args);
        clientBuff.emplace(clientBuff.begin(), ' ');
        clientBuff = convert(clientBuff, b1->operationId);
        clientBuff.emplace(clientBuff.begin(), ' ');
        clientBuff = convert(clientBuff, b1->objectId);
        clientBuff.emplace(clientBuff.begin(), ' ');
        clientBuff = convert(clientBuff, b1->gameId);
        cout << clientBuff.data() << endl;
//-----------------------------------------------------------------------------------------

#ifdef _WIN32
        if (clientBuff[0] == 'o' && clientBuff[1] == 'u' && clientBuff[2] == 't') {
            shutdown(ClientSock, SD_BOTH);
            closesocket(ClientSock);
            WSACleanup();
            return 0;
        }
#endif

        packet_size = send(ClientSock, clientBuff.data(), clientBuff.size(), 0);

#ifdef _WIN32
        if (packet_size == SOCKET_ERROR) {
            cout << "Can't send message to Server. Error # " << WSAGetLastError() << endl;
            closesocket(ClientSock);
            WSACleanup();
            return 1;
        }
#endif

        packet_size = recv(ClientSock, servBuff.data(), servBuff.size(), 0);

#ifdef _WIN32
        if (packet_size == SOCKET_ERROR) {
            cout << "Can't receive message from Server. Error # " << WSAGetLastError() << endl;
            closesocket(ClientSock);
            WSACleanup();
            return 1;
        }
        else
            cout << "Server message: " << servBuff.data() << endl;
    }
#endif

#ifdef _WIN32
    closesocket(ClientSock);
    WSACleanup();
#else
   close(ClientSock);
#endif

    return 0;
}
