#include "socket.h"

#include <typeinfo>


/*static*/
concurrent_queue<client_socket::S<3>> client_socket::caption;
concurrent_queue<client_socket::S<3>> client_socket::caption_min;


void client_socket::setSocket() {

    // ���� ����.
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return;
    }
    // Internet�� Stream ������� ���� ����

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {

        WSACleanup();
        CString error;
        error.Format(_T("\n/////// Invalid socket \n"));
        OutputDebugString(error);
        fputs("socket error", stderr);
        fputs("\n", stderr);
        //_getch();
        closesocket(sock); //before exit, close socket
        exit(1);
        //return 0;
    }


    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    inet_pton(AF_INET, addr, &servAddr.sin_addr.S_un.S_addr);
    servAddr.sin_port = htons(port);

    CString set_info;
    set_info.Format(_T("\n/////// TCP Socket created \n"));
    OutputDebugString(set_info);

}

wchar_t* client_socket::Utf8ToMultiByte(char* pszIn)
{

    int nLenOfUni = 0, nLenOfANSI = 0;
    wchar_t* uni_wchar = NULL;
    char* pszOut = NULL;

    // 1. utf8 Length
    if ((nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
        return 0;

    uni_wchar = new wchar_t[nLenOfUni + 1];
    memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));

    // 2. utf8 --> unicode
    nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);

    return uni_wchar;
}

int client_socket::byte2Int(char* src) {
    int s1 = src[0] & 0xFF;
    int s2 = src[1] & 0xFF;
    int s3 = src[2] & 0xFF;
    int s4 = src[3] & 0xFF;

    return ((s1 << 24) + (s2 << 16) + (s3 << 8) + (s4 << 0));
}

SOCKET client_socket::getSock() {
    return sock;
}

void client_socket::recvServer() {

    try {
        int iResult;
        int count;
        do {
            iResult = recv(sock, recvBUF, BUFSIZE, 0);
            count = 0;
            if (iResult > 0) {
                while (count < iResult) {

                    setlocale(LC_ALL, "KOREAN"); //�ܼ�â�� �ѱ� ����Ϸ��� �ݵ�� �̷��� �ؾ���..
                    //printf("Bytes received: %d\n", iResult);



                    struct client2server_header* recvhdr = (struct client2server_header*)(recvBUF + count);
                    //printf("struct size : %d", sizeof(struct client2server_header));
                    *(recvhdr->data_size) = ntohl(*(recvhdr->data_size));

                    /*printf("type:%d\n", recvhdr->type);
                    printf("data_size:%d\n", byte2Int(recvhdr->data_size));
                    for (int i = 0; i < 4; i++) {
                       printf("%d: %02x\n", i, recvhdr->data_size[i]);
                    }*/


                    /*for (int i = 0; i < 9; i++) {
                       printf("%d: %c\n", i, recvhdr->timestamp[i]);
                    }
                    printf("timestamp:%s\n", recvhdr->timestamp);*/

                    char* nickname = strtok((char*)(recvBUF + count) + sizeof(struct client2server_header), ":");
                    //printf("username: %s\n", nickname);
                    char* transcript = (char*)(recvBUF + count) + sizeof(struct client2server_header) + strlen(nickname) + 1;
                    //printf("transcript: %s\n", transcript);



                    wchar_t* stamp = Utf8ToMultiByte((char*)recvhdr->timestamp);
                    wchar_t* name = Utf8ToMultiByte(nickname);
                    wchar_t* talk = Utf8ToMultiByte(transcript);


                    S<3> temp;
                    temp.a[0] = stamp;
                    temp.a[1] = name;
                    temp.a[2] = talk;

                    if (recvhdr->type == 0) {
                        caption.push(temp);
                        //S<3> dest;
                        //caption.try_pop(dest);
                        //q.put(arr)
                        CString str_OneWay;
                        //str_OneWay.Format(_T("\n///////caption  [%s] %s : %s\n\n"), dest.a[0], dest.a[1], dest.a[2]);
                        //OutputDebugString(str_OneWay);
                    }
                    else if (recvhdr->type == 1) {
                        //note.push(temp);
                        caption_min.push(temp);
                        //S<3> dest;
                        //note.try_pop(dest);
                        //caption_min.try_pop(dest);
                        CString str_OneWay;
                        //str_OneWay.Format(_T("\n///////note  [%s] %s : %s\n\n"), dest.a[0], dest.a[1], dest.a[2]);
                        //OutputDebugString(str_OneWay);
                    }





                    count += 14 + byte2Int(recvhdr->data_size);


                }
            }

            else if (iResult == 0) {


                CString str_OneWay;
                str_OneWay.Format(_T("\n///////connection closed \n\n"));
                OutputDebugString(str_OneWay);
                break;
                //printf("Connection closed\n");
            }

            else {
                CString str_OneWay;
                str_OneWay.Format(_T("\n///////connection error [%d]\n\n"), WSAGetLastError());
                OutputDebugString(str_OneWay);
                //printf("recv failed: %d\n", WSAGetLastError());
            }







        } while (iResult > 0);
    }
    catch (int exception) {
        CString exception_msg;
        exception_msg.Format(_T("\n/////// EXCEPTION in recv packet from server  \n"));
        OutputDebugString(exception_msg);
    }

    return;
}


void client_socket::sendAudio() {

    //raw_audio dest;
    raw_audio* dest;


    while (1) {

        //if (audioQ.try_pop(dest) == false)
            //continue;
        if (audioQ_2.try_pop(dest) == false)
            continue;


        send2server(4, dest->data, dest->data_size, dest->user);


    }


}




void client_socket::sendFileName2server(char type, const char* data, int data_size, int file_size) {

    //data_size���ڴ� data�� �� ����Ʈ���� ��Ÿ���ش�.

    const char* packet;
    int pk_size; //��ü ��Ŷ�� �� ����Ʈ����
    int send_data_size = htonl(data_size);// ntohl(data_size); //-> change to big endian
    int send_file_data_size = htonl(file_size);



    //packet = type(1byte)+dataSize(4byte)+fileSize(4byte)+data 
    pk_size = data_size + sizeof(data_size) + sizeof(type) + sizeof(file_size);
    packet = (char*)malloc(sizeof(char) * (pk_size));



    memcpy((char*)packet, (char*)&type, sizeof(type));
    memcpy((char*)(packet + sizeof(type)), (char*)&send_data_size, sizeof(send_data_size));
    memcpy((char*)(packet + sizeof(type) + sizeof(send_data_size)), (char*)&send_file_data_size, sizeof(send_file_data_size));
    memcpy((char*)(packet + sizeof(type) + sizeof(send_data_size) + sizeof(send_file_data_size)), (char*)data, data_size);

    CString str_OneWay;
    str_OneWay.Format(_T("\n\n name"));
    //OutputDebugString(str_OneWay);

    for (int i = 0; i < pk_size; i++) {
        str_OneWay.Format(_T("%02x "), *(packet + i));
        //OutputDebugString(str_OneWay);
    }
    str_OneWay.Format(_T("\n\n"));
    //OutputDebugString(str_OneWay);


    try {
        int a = send(sock, packet, pk_size, 0);

        if (a == SOCKET_ERROR) {
            CString error;
            error.Format(_T("\n/////// error in sending data to server \n"));
            OutputDebugString(error);

        }
        else {
            CString send_info;
            send_info.Format(_T("\n/////// Send data to server size=%d\n"), pk_size);
            OutputDebugString(send_info);

            send_info.Format(_T("\n/////// type=%d\n"), type);
            //OutputDebugString(send_info);
        }
    }
    catch (int exception) {
        CString exception_msg;
        exception_msg.Format(_T("\n/////// EXCEPTION in sending data to server \n"));
        OutputDebugString(exception_msg);
    }

    try {
        free((char*)packet); //�ǽɽ�����
    }
    catch (int exception) {
        CString exception_msg;
        exception_msg.Format(_T("\n/////// EXCEPTION in memory free in packet  \n"));
        OutputDebugString(exception_msg);
    }
    return;
}



void client_socket::send2server(char type, const char* data, int data_size, const char* name) {

    //data_size���ڴ� data�� �� ����Ʈ���� ��Ÿ���ش�.

    const char* packet;
    int pk_size; //��ü ��Ŷ�� �� ����Ʈ����
    int send_data_size = htonl(data_size);// ntohl(data_size); //-> change to big endian
    int name_size = strlen(name);
    int send_name_size = htonl(name_size);

    char timestamp[9];
    time_t curTime = time(NULL);
    struct tm* pLocal = localtime(&curTime);
    sprintf(timestamp, "%02d:%02d:%02d", pLocal->tm_hour, pLocal->tm_min, pLocal->tm_sec);


    CString send_info;


    pk_size = data_size + sizeof(send_data_size) + sizeof(type) + strlen(timestamp) + name_size + sizeof(send_name_size);

    send_info.Format(_T("\n/////// pk_size=%d\n"), pk_size);
    //OutputDebugString(send_info);

    packet = (char*)malloc(sizeof(char) * (pk_size));

    send_info.Format(_T("\n/////// pk_size=%d\n"), pk_size);
    //OutputDebugString(send_info);

    CString str_OneWay;
    for (int i = 0; i < strlen(name); i++) {
        //str_OneWay.Format(_T("\n///////%02x\n\n"), *(name + i));
        //OutputDebugString(str_OneWay);
    }

    memcpy((char*)packet, (char*)&type, sizeof(type));
    memcpy((char*)(packet + sizeof(type)), (char*)&send_data_size, sizeof(send_data_size));
    memcpy((char*)(packet + sizeof(type) + sizeof(send_data_size)), (char*)timestamp, strlen(timestamp));
    memcpy((char*)(packet + sizeof(type) + sizeof(send_data_size) + strlen(timestamp)), (char*)&send_name_size, sizeof(send_name_size));
    memcpy((char*)(packet + sizeof(type) + sizeof(send_data_size) + strlen(timestamp) + sizeof(send_name_size)), (char*)name, name_size);
    memcpy((char*)(packet + sizeof(type) + sizeof(send_data_size) + strlen(timestamp) + sizeof(send_name_size) + name_size), (char*)data, data_size);

    free((char*)data);

    str_OneWay.Format(_T("\n\n new "));
    //OutputDebugString(str_OneWay);
    //for (int i = 0; i < pk_size; i++) {
        //str_OneWay.Format(_T("%02x "), *(packet + i));
        //OutputDebugString(str_OneWay);
    //}
    //str_OneWay.Format(_T("\n\n"));
    //OutputDebugString(str_OneWay);
    try {
        int a = send(sock, packet, pk_size, 0);
        if (a == SOCKET_ERROR) {
            CString error;
            error.Format(_T("\n/////// error in sending data to server \n"));
            OutputDebugString(error);

        }
        else {
            //CString send_info;
            send_info.Format(_T("\n/////// Send data to server size=%d\n"), pk_size);
            //OutputDebugString(send_info);

            send_info.Format(_T("\n/////// type=%d\n"), type);
            //OutputDebugString(send_info);
        }
    }



    catch (int exception) {
        CString exception_msg;
        exception_msg.Format(_T("\n/////// EXCEPTION in sending data to server \n"));
        OutputDebugString(exception_msg);
    }
    try {
        free((char*)packet); //�ǽɽ�����
    }
    catch (int exception) {
        CString exception_msg;
        exception_msg.Format(_T("\n/////// EXCEPTION in memory free in packet  \n"));
        OutputDebugString(exception_msg);
    }
    return;
}


void client_socket::send2server(char type, const char* data, int data_size) {

    //data_size���ڴ� data�� �� ����Ʈ���� ��Ÿ���ش�.

    const char* packet;
    int pk_size; //��ü ��Ŷ�� �� ����Ʈ����
    int send_data_size = htonl(data_size);// ntohl(data_size); //-> change to big endian

    if (type == 4) {
        //if audio raw data
        //packet = type(1byte)+dataSize(4byte)+time(8byte)+data
        char timestamp[9];
        time_t curTime = time(NULL);
        struct tm* pLocal = localtime(&curTime);
        sprintf(timestamp, "%02d:%02d:%02d", pLocal->tm_hour, pLocal->tm_min, pLocal->tm_sec);

        pk_size = data_size + sizeof(send_data_size) + sizeof(type) + strlen(timestamp);
        packet = (char*)malloc(sizeof(char) * (pk_size));


        memcpy((char*)packet, (char*)&type, sizeof(type));
        memcpy((char*)(packet + sizeof(type)), (char*)&send_data_size, sizeof(send_data_size));
        memcpy((char*)(packet + sizeof(type) + sizeof(send_data_size)), (char*)timestamp, strlen(timestamp));
        memcpy((char*)(packet + sizeof(type) + sizeof(send_data_size) + strlen(timestamp)), (char*)data, data_size);

        //free((char*)data);
    }
    else {

        //packet = type(1byte)+dataSize(4byte)+data 
        pk_size = data_size + sizeof(data_size) + sizeof(type);
        packet = (char*)malloc(sizeof(char) * (pk_size));



        memcpy((char*)packet, (char*)&type, sizeof(type));
        memcpy((char*)(packet + sizeof(type)), (char*)&send_data_size, sizeof(send_data_size));
        memcpy((char*)(packet + sizeof(type) + sizeof(send_data_size)), (char*)data, data_size);

        CString str_OneWay;
        str_OneWay.Format(_T("\n\n name"));
        //OutputDebugString(str_OneWay);

        for (int i = 0; i < pk_size; i++) {
            str_OneWay.Format(_T("%02x "), *(packet + i));
            //OutputDebugString(str_OneWay);
        }
        str_OneWay.Format(_T("\n\n"));
        //OutputDebugString(str_OneWay);
    }

    try {
        int a = send(sock, packet, pk_size, 0);

        if (a == SOCKET_ERROR) {
            CString error;
            error.Format(_T("\n/////// error in sending data to server \n"));
            OutputDebugString(error);

        }
        else {
            CString send_info;
            send_info.Format(_T("\n/////// Send data to server size=%d\n"), pk_size);
            //OutputDebugString(send_info);

            send_info.Format(_T("\n/////// type=%d\n"), type);
            //OutputDebugString(send_info);
        }
    }
    catch (int exception) {
        CString exception_msg;
        exception_msg.Format(_T("\n/////// EXCEPTION in sending data to server \n"));
        OutputDebugString(exception_msg);
    }

    try {
        free((char*)packet); //�ǽɽ�����
    }
    catch (int exception) {
        CString exception_msg;
        exception_msg.Format(_T("\n/////// EXCEPTION in memory free in packet  \n"));
        OutputDebugString(exception_msg);
    }
    return;
}



void client_socket::send2server(const char* input, int size) {

    //strncpy_s(message, input, size);

    int a = send(sock, input, size, 0);
    if (a == SOCKET_ERROR) {
        CString error;
        error.Format(_T("\n/////// error in sending data to server \n"));
        OutputDebugString(error);

    }
    else {
        CString send_info;
        send_info.Format(_T("\n/////// Send data to server \n"));
        OutputDebugString(send_info);

    }





    return;

}

void client_socket::send2server() {





    while (1) {

        cout << "Message : ";
        cin >> message;

        if (strcmp(message, "exit") == 0) {
            break;
        }


        send(sock, message, (int)strlen(message), 0);
    }


    return;

}

void client_socket::connectSocket() {
    if (connect(sock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
        WSACleanup();

        CString error;
        error.Format(_T("\n/////// TCP connection error \n"));
        OutputDebugString(error);
        fputs("connection error", stderr);
        fputs("\n", stderr);
        //_getch();
        exit(1);
    }

    CString success_info;
    success_info.Format(_T("\n/////// TCP connection success \n"));
    OutputDebugString(success_info);


}


void client_socket::closeSocket() {
    closesocket(sock);
    WSACleanup();
    CString closeSock;
    closeSock.Format(_T("\n/////// close socket \n"));
    OutputDebugString(closeSock);
    //_getch();

    return;
}