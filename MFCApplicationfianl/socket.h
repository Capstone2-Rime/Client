#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <winsock2.h>
#include <WS2tcpip.h>
#include <cstdio>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <time.h>
//CString
#include "atlstr.h" 
#pragma comment(lib, "ws2_32.lib")
#define BUFSIZE 4096

#include <concurrent_queue.h>
#include <mutex>

using namespace std;
using namespace Concurrency;

class client_socket {
private:
    WSADATA wsaData;
    SOCKADDR_IN servAddr;

    SOCKET sock;
    char addr[15] = "192.168.198.56";//"192.168.35.128";//"192.168.35.192";//"192.168.11.7";//"192.168.35.80";//"192.168.11.7";//"192.168.253.56";//"192.168.35.173";//"172.20.10.6"; //"13.125.121.12";//  //"10.210.60.153"; //ip�ּҴ� ����� �� ����(�Ź� ������ ��)
    int port = 12000;

public:
    char recvBUF[BUFSIZE];
    char message[BUFSIZE];
    void setSocket();
    void recvServer();
    void send2server(const char* input, int size); //char* -> const char*
    void send2server(char type, const char* data, int data_size);
    void send2server(char type, const char* data, int data_size, const char* name);
    void sendFileName2server(char type, const char* data, int data_size, int file_size);
    void sendAudio();
    void send2server();
    void connectSocket();
    void closeSocket();
    int byte2Int(char* src);
    wchar_t* Utf8ToMultiByte(char* pszIn);
    SOCKET getSock();


    mutex mtx_lock;

    template<int N>
    struct S { wchar_t* a[N]; };
    static concurrent_queue<S<3>> caption;
    //concurrent_queue<S<3>> note;
    static concurrent_queue<S<3>> caption_min;

    struct raw_audio {
        const char* data;
        unsigned int data_size;
        char* user;
    };

    concurrent_queue<raw_audio> audioQ;
    concurrent_queue<raw_audio*> audioQ_2;

    struct client2server_header
    {
        char type;
        char data_size[4];
        char timestamp[9]; // hh:mm:ss\0
        //std::string str;
    };


};