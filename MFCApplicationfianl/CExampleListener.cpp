//#include "stdafx.h"

//not use
//onChatNewMessageNotify, messageitem
#include "zoom_instant_sdk_chat_message_interface.h"
//m_pPasswordHandler
#include "zoom_instant_sdk_password_handler_interface.h"


#include "CExampleListener.h"

//CreateZoomInstantSDKObj()
#include "zoom_instant_sdk_api.h"
//CString
#include "atlstr.h" 
//IZoomInstantSDKSession m_pSession
#include "zoom_instant_sdk_session_info_interface.h"
#include "Session.h"

unsigned char* CExampleListener::yBuffer;
unsigned char* CExampleListener::uBuffer;
unsigned char* CExampleListener::vBuffer;

int CExampleListener::S_width;
int CExampleListener::S_height;

CExampleListener::CExampleListener() {

    /*Initialize the SDK*/
    m_pInstantSDK = CreateZoomInstantSDKObj();

    ZoomInstantSDKInitParams initParams;
    initParams.domain = L"https://zoom.us";
    initParams.enableIndirectRawdata = false;
    initParams.enableLog = true;
    initParams.audioRawDataMemoryMode = ZoomInstantSDKRawDataMemoryModeStack;
    initParams.videoRawDataMemoryMode = ZoomInstantSDKRawDataMemoryModeStack;
    initParams.shareRawDataMemoryMode = ZoomInstantSDKRawDataMemoryModeStack;
    int returnVal_initialize = -1;
    returnVal_initialize = m_pInstantSDK->initialize(initParams);
    CString str_init;
    if (returnVal_initialize == ZoomInstantSDKErrors_Success) {
        str_init.Format(_T("\n///////0.SUCCESS m_pInstantSDK->initialize(initParams)\n\n"));
    }
    else {
        str_init.Format(_T("\n///////0.FAIL m_pInstantSDK->initialize(initParams)\n\n"));
    }
    OutputDebugString(str_init);
    /*Listen for callback events*/
    m_pInstantSDK->addListener(this);

    //byh 0529
    /*add code for connecting to server
    connect_socket = new client_socket();
    connect_socket->setSocket();
    connect_socket->connectSocket();*/

    S_width = -1;
    S_height = -1;




}

void CExampleListener::Render(IZoomInstantSDKUser* pUser) {


}
void CExampleListener::onRawDataFrameReceived(YUVRawDataI420* data_)
{

}



void CExampleListener::onRawDataStatusChanged(RawDataStatus status)
{
    if (status == RawData_On)
    {
        // Now subscribed to user's data.
    }
    else
    {
        // No longer subscribed to user's data.
    }
}



/*      */
CExampleListener::CExampleListener(TCHAR word[]) {

    if (word == NULL) {
        OutputDebugString(_T("\n\nupload null\n\n"));
    }
    else {
        OutputDebugString(_T("\n\n"));
        OutputDebugString(word);
        OutputDebugString(_T("\n\n"));
    }



    /*Initialize the SDK*/
    m_pInstantSDK = CreateZoomInstantSDKObj();

    ZoomInstantSDKInitParams initParams;
    initParams.domain = L"https://zoom.us";
    initParams.enableIndirectRawdata = false;
    initParams.enableLog = true;
    initParams.audioRawDataMemoryMode = ZoomInstantSDKRawDataMemoryModeStack;
    initParams.videoRawDataMemoryMode = ZoomInstantSDKRawDataMemoryModeStack;
    initParams.shareRawDataMemoryMode = ZoomInstantSDKRawDataMemoryModeStack;
    int returnVal_initialize = -1;
    returnVal_initialize = m_pInstantSDK->initialize(initParams);
    CString str_init;
    if (returnVal_initialize == ZoomInstantSDKErrors_Success) {
        str_init.Format(_T("\n///////0.SUCCESS m_pInstantSDK->initialize(initParams)\n\n"));
    }
    else {
        str_init.Format(_T("\n///////0.FAIL m_pInstantSDK->initialize(initParams)\n\n"));
    }
    OutputDebugString(str_init);
    /*Listen for callback events*/
    m_pInstantSDK->addListener(this);



    //f.open("test.raw", std::ostream::binary);

    //add code for connecting to server
    connect_socket = new client_socket();
    connect_socket->setSocket();
    connect_socket->connectSocket();

    char file_name[50];
    WideCharToMultiByte(CP_ACP, 0, word, 50, file_name, 50, NULL, NULL);
    connect_socket->sendFileName2server(5, file_name, strlen(file_name), 1);

    /*
        ////add code for course note
        input_f.open(word, std::ifstream::binary);

        char file_name[50];
        WideCharToMultiByte(CP_ACP, 0, word, 50, file_name, 50, NULL, NULL);
        //connect_socket->send2server(5,file_name, strlen(file_name));



        if (input_f) {
            // seekg    ̿         ũ
            input_f.seekg(0, input_f.end);
            int length = (int)input_f.tellg();
            input_f.seekg(0, input_f.beg);

            connect_socket->sendFileName2server(5, file_name, strlen(file_name), length);
            CString str_len;
            str_len.Format(_T("///////// file size=%d\n"), length);
            OutputDebugString(str_len);

            // malloc      ޸   Ҵ
            char* buffer = (char*)malloc(length);



            // read data as a block:

            input_f.read((char*)buffer, length);
            input_f.close();
            //connect_socket->send2server(6, (buffer), length);
            int counter = 0;
            int send_counter = 1;
            int unit = 4096;
            while (counter != length) {
                if (length - counter < unit) {
                    //CString str_cnt;
                    //str_cnt.Format(_T("///////// send counter=%d\n"), send_counter);
                    //OutputDebugString(str_cnt);
                    connect_socket->send2server(6, (buffer + counter), length - counter);
                    counter += length - counter;
                    send_counter++;
                }
                else {
                    //CString str_cnt;
                    //str_cnt.Format(_T("///////// send counter=%d\n"), send_counter);
                    //OutputDebugString(str_cnt);
                    connect_socket->send2server(6, (buffer + counter), unit);
                    counter += unit;
                    send_counter++;
                    Sleep(5);
                }

            }


            free((char*)buffer);
            //wait reply from server
            int iResult = recv(connect_socket->getSock(), connect_socket->recvBUF, BUFSIZE, 0);
            //connect_socket->send2server(6, "finish", strlen("finish"));
        }
    */
    //ȸ             
    char sessionType = 16;
    connect_socket->send2server(1, &sessionType, sizeof(char));


    //connect_socket->closeSocket();


    /*

       m_pUserHelper= m_pInstantSDK->getUserHelper();
       CString cstrInfo_UserHelper;
       if (m_pUserHelper != NULL) {
          cstrInfo_UserHelper.Format(_T("///////getUserHelper Success \n"));
       }
       else if (m_pUserHelper == NULL) {
          cstrInfo_UserHelper.Format(_T("///////getUserHelper Fail \n"));
       }
       OutputDebugString(cstrInfo_UserHelper);

    */




}

void CExampleListener::JoinSession(ZoomInstantSDKSessionContext* sessionContext) {
    m_pInstantSDK->getVideoHelper()->stopVideo();

    m_pSessionContext = sessionContext;
    m_pSession = m_pInstantSDK->joinSession(*m_pSessionContext);
    CString str_jS;
    if (m_pSession != NULL) {
        str_jS.Format(_T("\n///////1.SUCCESS m_pInstantSDK->joinSession(*m_pSessionContext)\n\n"));
    }
    else {
        str_jS.Format(_T("\n///////1.FAIL m_pInstantSDK->joinSession(*m_pSessionContext)\n\n"));
    }
    OutputDebugString(str_jS);



}




//Get notified when local user successfully join a session
void CExampleListener::onSessionJoin()
{

    IZoomInstantSDKSession* sessionInfo = m_pInstantSDK->getSessionInfo();



    CString cstrInfo_onSessionJoin;
    cstrInfo_onSessionJoin.Format(_T("\n///////Myself__onSessionJoin: my name=%s, session name=%s, host name= %s \n"),
        sessionInfo->getMyself()->getUserName(),
        sessionInfo->getSessionName(),
        sessionInfo->getSessionHostName()

    );
    OutputDebugString(cstrInfo_onSessionJoin);

    /*Host*/
    CString cstrInfo_Host;
    if (sessionInfo->getMyself()->isHost()) {
        cstrInfo_Host.Format(_T("///////I'm Host. My name=%s, Host name=%s \n\n"),
            sessionInfo->getMyself()->getUserName(),
            sessionInfo->getSessionHostName()
        );
    }
    else {
        cstrInfo_Host.Format(_T("///////I'm not Host. My name=%s, Host name=%s \n\n"),
            sessionInfo->getMyself()->getUserName(),
            sessionInfo->getSessionHostName()
        );
    }
    OutputDebugString(cstrInfo_Host);

    /*send user name to server*/
    /*CString str_form;
    str_form.Format(_T("%s"), sessionInfo->getMyself()->getUserName());
    const char* str2;
    str2 = (CStringA)str_form;
    strncpy_s(connect_socket->message, str2, strlen(str2));
    connect_socket->send2server(2,connect_socket->message, strlen(connect_socket->message));

    for (int i = 0; i < strlen(connect_socket->message); i++) {
        str_form.Format(_T("\n///////%02x\n\n"), *(connect_socket->message + i));
        OutputDebugString(str_form);
    }*/



    /*audioStatus*/
    ZoomInstantSDKAudioStatus audioStatus_myself;
    audioStatus_myself = sessionInfo->getMyself()->getAudioStatus();


    audioStatus_myself.audioType;

    audioStatus_myself.isMuted;
    audioStatus_myself.isTalking;

    IZoomInstantSDKAudioHelper* pAudioHelper = m_pInstantSDK->getAudioHelper();


    /*
    (1)audioStatus_myself.audioType;
    (2)audioStatus_myself.isMuted;
    getAudioHelper()->subscribe()
    */

    //(1)audioStatus_myself.audioType;
    if (audioStatus_myself.audioType == ZoomInstantSDKAudioType_None) {
        // User(myself)'s audio is not connected.
        //OutputDebugString(_T("\n///////My audio is not connected. audioStatus_myself.audioType == ZoomInstantSDKAudioType_None\n\n"));
        CString str_startAudio;
        // Get the IZoomInstantSDKAudioHelper to perform audio actions.
        IZoomInstantSDKAudioHelper* pAudioHelper = m_pInstantSDK->getAudioHelper();
        if (pAudioHelper) {
            // Connect User's audio.
            int return_startAudio;
            return_startAudio = pAudioHelper->startAudio();
            if (return_startAudio == ZoomInstantSDKErrors_Success) {
                str_startAudio.Format(_T("\n///////2.SUCCESS return_startAudio == ZoomInstantSDKErrors_Success\n\n"));
                OutputDebugString(str_startAudio);

                /*
                //print changed audioType
                CString str_changedAudioType;
                if (audioStatus_myself.audioType == ZoomInstantSDKAudioType_VOIP) {
                   str_changedAudioType.Format(_T("///////audioStatus_myself.audioType == ZoomInstantSDKAudioType_VOIP\n\n"));
                }
                else if (audioStatus_myself.audioType == ZoomInstantSDKAudioType_None) {
                   str_changedAudioType.Format(_T("///////audioStatus_myself.audioType == ZoomInstantSDKAudioType_None\n\n"));
                }
                OutputDebugString(str_changedAudioType);
                */

            }
            else {
                str_startAudio.Format(_T("\n///////2.FAIL return_startAudio =%d \n\n"), return_startAudio);
                OutputDebugString(str_startAudio);
            }

        }
        else {
            OutputDebugString(_T("\n///////2.pAudioHelper is NULL. pAudioHelper = m_pInstantSDK->getAudioHelper();\n\n"));
        }
    }
    else if (audioStatus_myself.audioType == ZoomInstantSDKAudioType_VOIP)
    {
        // User is already connected to audio.
        OutputDebugString(_T("\n///////2.User's audio is already connected. audioType == ZoomInstantSDKAudioType_VOIP\n\n"));
    }

    //(2)audioStatus_myself.isMuted;
    CString str_isMuted;
    if (audioStatus_myself.isMuted) {
        //str_isMuted.Format(_T("\n///////I'm muted.\n\n"));

        //add code for unmute localUser(=myself)
        int return_unMuteAudio;
        CString str_unMuteAudio;
        return_unMuteAudio = m_pInstantSDK->getAudioHelper()->unMuteAudio(sessionInfo->getMyself());
        if (return_unMuteAudio == ZoomInstantSDKErrors_Success) {
            str_unMuteAudio.Format(_T("\n///////3.SUCCESS return_unMuteAudio == ZoomInstantSDKErrors_Success\n\n"));
        }
        else {
            str_unMuteAudio.Format(_T("\n///////3.FAIL return_unMuteAudio =%d \n\n"), return_unMuteAudio);
        }
        OutputDebugString(str_unMuteAudio);

    }
    else {
        OutputDebugString(_T("\n///////3.I'm not muted.\n\n"));
    }
    OutputDebugString(str_isMuted);

    /*strncpy_s(connect_socket->message, "start",strlen("start"));
     for (int i = 0; i < 3; i++) {
         connect_socket->send2server(connect_socket->message, strlen("start"));
     }*/



     //getAudioHelper()->subscribe()
    int return_subscribeAudio;
    return_subscribeAudio = m_pInstantSDK->getAudioHelper()->subscribe();
    CString str_subscribeAudio;
    if (return_subscribeAudio == ZoomInstantSDKErrors_Success) {
        str_subscribeAudio.Format(_T("\n///////4.SUCCESS return_subscribeAudio == ZoomInstantSDKErrors_Success\n\n"));
    }
    else {
        str_subscribeAudio.Format(_T("\n///////4.FAIL return_subscribeAudio =%d \n\n"), return_subscribeAudio);
    }
    OutputDebugString(str_subscribeAudio);


    //byh1
    t1 = thread(&client_socket::recvServer, connect_socket);
    t2 = thread(&client_socket::sendAudio, connect_socket);



    /*CSession ssDlg;
    INT_PTR nResponse =ssDlg.DoModal();
    if (nResponse == IDOK)
    {
    }
    else if (nResponse == IDCANCEL)
    {
    }*/
    /*int check_onSessionJoin = MessageBox(NULL,
        cstrInfo_onSessionJoin,
        m_pSession->getSessionName(),
        MB_OKCANCEL);*/
    
    
    /*int check_onSessionJoin = MessageBox(NULL,
        _T(""),
        _T("회의 시작"),
        MB_OKCANCEL);
    if (check_onSessionJoin == IDOK) {
        //m_pInstantSDK->leaveSession(true);
       // m_pInstantSDK->leaveSession(false);
    } //if user click ok in message box then return IDOK -> leave session(if arg is false)
    else if (check_onSessionJoin == IDCANCEL) {
        m_pInstantSDK->leaveSession(false);
    }*/



}
void CExampleListener::onSessionLeave()
{
    // You have successfully left the session.
    //add code for close socket
    try {
        connect_socket->closeSocket();
        CString strInfo_onSessionLeave;

        strInfo_onSessionLeave.Format(_T("///////Myself__onSessionLeave \n"));
        OutputDebugString(strInfo_onSessionLeave);
    }
    catch (int exception) {
        CString exception_msg;
        exception_msg.Format(_T("\n/////// EXCEPTION in onSessionLeave  \n"));
        OutputDebugString(exception_msg);
    }

}
//Get notified when other users successfully join a session
void CExampleListener::onUserJoin(IZoomInstantSDKUserHelper* pUserHelper, IInstantSDKVector<IZoomInstantSDKUser*>* userList)
{

    CString strInfo_onUserJoin;
    IZoomInstantSDKUser* pUser;
    int count = userList->GetCount();
    for (int i = 0; i < count; i++)
    {
        pUser = userList->GetItem(i);


        if (!pUser) continue;
        strInfo_onUserJoin.Format(_T("///////A user joined the session: name=%s\n"), pUser->getUserName());

        OutputDebugString(strInfo_onUserJoin);
        Render(pUser);
    }


}

void CExampleListener::onUserLeave(IZoomInstantSDKUserHelper* pUserHelper, IInstantSDKVector<IZoomInstantSDKUser*>* userList)
{

    CString strInfo_onUserLeave;
    IZoomInstantSDKUser* pUser;
    int count = userList->GetCount();
    for (int i = 0; i < count; i++)
    {
        pUser = userList->GetItem(i);
        if (!pUser) continue;
        strInfo_onUserLeave.Format(_T("///////A user left the session \n"));
        OutputDebugString(strInfo_onUserLeave);
    }
}

//Get notified of operation results and SDK errors
void CExampleListener::onError(ZoomInstantSDKErrors errorCode, int detailErrorCode)
{
    CString info;

    switch (errorCode)
    {
    case ZoomInstantSDKErrors_Meeting_Disconnecting:
        info.Format(_T("\n///////onError(): Disconnecting from session, Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;
    case ZoomInstantSDKErrors_Meeting_Reconnecting:
        info.Format(_T("\n///////onError(): Reconnecting to session, Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;
    case ZoomInstantSDKErrors_Meeting_Join_Failed:
        info.Format(_T("\n///////onError(): Failed to join session, Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;

        /*      ۼ */
    case ZoomInstantSDKErrors_Wrong_Usage:
        info.Format(_T("\n///////onError(): ZoomInstantSDKErrors_Wrong_Usage, Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;
    case ZoomInstantSDKErrors_Meeting_Audio_Error:
        info.Format(_T("\n///////onError(): ZoomInstantSDKErrors_Meeting_Audio_Error, Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;
    case ZoomInstantSDKErrors_RAWDATA_AUDIO_MODULE_NOT_READY:
        info.Format(_T("\n///////onError(): ZoomInstantSDKErrors_RAWDATA_AUDIO_MODULE_NOT_READY, Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;
    case ZoomInstantSDKErrors_RAWDATA_AUDIO_MODULE_ERROR:
        info.Format(_T("\n///////onError(): ZoomInstantSDKErrors_RAWDATA_AUDIO_MODULE_ERROR, Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;
    case ZoomInstantSDKErrors_RAWDATA_NO_AUDIO_DATA:
        info.Format(_T("\n///////onError(): ZoomInstantSDKErrors_RAWDATA_NO_AUDIO_DATA, Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;

        //7
    case ZoomInstantSDKErrors_Invalid_Parameter:
        info.Format(_T("\n///////onError(): ZoomInstantSDKErrors_Invalid_Parameter, Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;

    default:
        info.Format(_T("\n///////onError(): Error:%d DetailCode: %d\n\n"), errorCode, detailErrorCode);
        break;
    }
    OutputDebugString(info);
}


//Get notified when a user's active audio changes
/* onUserActiveAudioChanged is different from onUserAudioStatusChanged.
onUserActiveAudioChanged is called when a given user's audio changes,
while onUserAudioStatusChanged is called when the user's audio status changes.
For example, if the user is unmuted and is using their device's microphone,
this callback will be triggered whenever their microphone detects a noise.*/
void CExampleListener::onUserActiveAudioChanged(IZoomInstantSDKAudioHelper* pAudioHelper, IInstantSDKVector<IZoomInstantSDKUser*>* userList)
{

    CString strInfo_user;
    IZoomInstantSDKUser* pUser;
    CString strInfo_audioType;
    CString strInfo_isMuted;
    ZoomInstantSDKAudioStatus audioStatus_pUser;

    int count = userList->GetCount();
    for (int i = 0; i < count; i++)
    {
        pUser = userList->GetItem(i);
        //strInfo_user.Format(_T("\n///////A user's audio status changed: userid=%s, name=%s"), pUser->getUserId(), pUser->getUserName());
        strInfo_user.Format(_T("\n///////ACTIVE user's audio status changed: name=%s"), pUser->getUserName());
        //OutputDebugString(strInfo_user);



        audioStatus_pUser = pUser->getAudioStatus();
        //audioType
        if (audioStatus_pUser.audioType == ZoomInstantSDKAudioType_VOIP) {
            strInfo_audioType.Format(_T(", audioType == ZoomInstantSDKAudioType_VOIP\n\n"));
        }
        else if (audioStatus_pUser.audioType == ZoomInstantSDKAudioType_None) {
            strInfo_audioType.Format(_T(", audioType == ZoomInstantSDKAudioType_None\n\n"));
        }
        //OutputDebugString(strInfo_audioType);
        /*isMuted
        if (audioStatus_pUser.isMuted) {
           strInfo_isMuted.Format(_T(", isMuted == true\n\n"));
        }
        else{
           strInfo_isMuted.Format(_T(", isMuted == false\n\n"));
        }
        OutputDebugString(strInfo_isMuted);
        */



    }


}

void CExampleListener::onMixedAudioRawDataReceived(AudioRawData* data_)
{
    // Access mixed data for the whole session here.
    if (!data_) return;

    unsigned int audioChannelNumber = data_->GetChannelNum();
    unsigned int audioSampleRate = data_->GetSampleRate();
    unsigned int bufferLength = data_->GetBufferLen();//640

    char* buffer = data_->GetBuffer();
    //CString str_Mix;

    //connect_socket->send2server(buffer, bufferLength);

    //f.write(buffer, bufferLength);

    //str_Mix.Format(_T("\n///////Mix, len=%d,sizeof=%d,bufferlength=%d ,channel=%d\n\n"), strlen(buffer),sizeof(buffer),bufferLength,audioChannelNumber);
    //OutputDebugString(str_Mix);
    //connect_socket->send2server(buffer, bufferLength);

    /*
    int size_one = strlen(buffer);
    CString strInfo_len_one;
    strInfo_len_one.Format(_T("\n///////length of Mixedbuffer=%d \n\n"), size_one);
    OutputDebugString(strInfo_len_one);

    MessageBox(NULL,
       strInfo_len_one,
       strInfo_len_one,
       MB_OKCANCEL);*/
}

void CExampleListener::onOneWayAudioRawDataReceived(AudioRawData* data_, IZoomInstantSDKUser* pUser)
{
    //return;
    // Access user-specific raw data here for the user associated with the user.
    if (!data_) return;

    unsigned int audioChannelNumber = data_->GetChannelNum();
    unsigned int audioSampleRate = data_->GetSampleRate(); //32000
    unsigned int bufferLength = data_->GetBufferLen(); //640

    char* buffer = data_->GetBuffer();

    CString str_OneWay;
    str_OneWay.Format(_T("\n///////OneWay, bufferlen=%d strlen=%d\n\n"), bufferLength, strlen(buffer));



    CString str_form;


    char* buffer_ptr = new char;

    buffer_ptr = (char*)malloc(bufferLength * sizeof(char));


    memcpy(buffer_ptr, buffer, bufferLength * sizeof(char));




    str_form.Format(_T("%s"), (wchar_t*)pUser->getUserName()); //   ⼭ eaxception



    wchar_t* wchar_str;
    char* str2;
    int char_str_len;

    wchar_str = str_form.GetBuffer(str_form.GetLength());
    char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
    str2 = new char[char_str_len];

    WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, str2, char_str_len, 0, 0);



    //client_socket::raw_audio a;
    //a.data = buffer_ptr;
    //a.data_size = bufferLength;
    //a.user = str2;


    //2
    client_socket::raw_audio* a2;
    a2 = (client_socket::raw_audio*)malloc(sizeof(client_socket::raw_audio));
    a2->data = buffer_ptr;
    a2->data_size = bufferLength;
    a2->user = str2;
    connect_socket->audioQ_2.push(a2);



    //connect_socket->send2server(4, buffer_ptr, bufferLength, str2);



}





















//not use




void CExampleListener::onUserVideoStatusChanged(IZoomInstantSDKVideoHelper* pVideoHelper, IInstantSDKVector<IZoomInstantSDKUser*>* userList)
{
    CString strInfo;
    IZoomInstantSDKUser* pUser;
    int count = userList->GetCount();

    for (int i = 0; i < count; i++)
    {
        pUser = userList->GetItem(i);
        strInfo.Format(_T("///////A user's video status changed: userid=%s, name=%s, status=%s"), pUser->getUserId(), pUser->getUserName(), pUser->getVideoStatus());
        OutputDebugString(strInfo);
    }
}

void CExampleListener::onUserAudioStatusChanged(IZoomInstantSDKAudioHelper* pAudioHelper, IInstantSDKVector<IZoomInstantSDKUser*>* userList)
{
    CString strInfo_user;
    IZoomInstantSDKUser* pUser;
    CString strInfo_audioType;
    CString strInfo_isMuted;
    ZoomInstantSDKAudioStatus audioStatus_pUser;

    int count = userList->GetCount();
    for (int i = 0; i < count; i++)
    {
        pUser = userList->GetItem(i);
        //strInfo_user.Format(_T("\n///////A user's audio status changed: userid=%s, name=%s"), pUser->getUserId(), pUser->getUserName());
        strInfo_user.Format(_T("\n///////A user's audio status changed: name=%s"), pUser->getUserName());
        OutputDebugString(strInfo_user);



        audioStatus_pUser = pUser->getAudioStatus();
        //audioType
        if (audioStatus_pUser.audioType == ZoomInstantSDKAudioType_VOIP) {
            strInfo_audioType.Format(_T(", audioType == ZoomInstantSDKAudioType_VOIP\n\n"));
        }
        else if (audioStatus_pUser.audioType == ZoomInstantSDKAudioType_None) {
            strInfo_audioType.Format(_T(", audioType == ZoomInstantSDKAudioType_None\n\n"));
        }
        OutputDebugString(strInfo_audioType);
        /*isMuted
        if (audioStatus_pUser.isMuted) {
           strInfo_isMuted.Format(_T(", isMuted == true\n\n"));
        }
        else{
           strInfo_isMuted.Format(_T(", isMuted == false\n\n"));
        }
        OutputDebugString(strInfo_isMuted);
        */



    }
}

void CExampleListener::onUserShareStatusChanged(IZoomInstantSDKShareHelper* pShareHelper, IZoomInstantSDKUser* pUser, ZoomInstantSDKShareStatus status)
{
    CString strInfo;
    const zchar_t* userId = pUser->getUserId();

    switch (status)
    {
    case ZoomInstantSDKShareStatus_None:
        strInfo.Format(_T("///////User's share status changed to None: userid=%s, name=%s"), userId, pUser->getUserName());
        break;
    case ZoomInstantSDKShareStatus_Pause:
        strInfo.Format(_T("///////User paused sharing: userid=%s, name=%s"), userId, pUser->getUserName());
        break;
    case ZoomInstantSDKShareStatus_Resume:
        strInfo.Format(_T("///////User resumed sharing: userid=%s, name=%s"), userId, pUser->getUserName());
        break;
    case ZoomInstantSDKShareStatus_Start:
        strInfo.Format(_T("///////User began sharing: userid=%s, name=%s"), userId, pUser->getUserName());
        break;
    case ZoomInstantSDKShareStatus_Stop:
        strInfo.Format(_T("///////User stopped sharing: userid=%s, name=%s"), userId, pUser->getUserName());
        break;
    }

    OutputDebugString(strInfo);
}

void CExampleListener::onLiveStreamStatusChanged(IZoomInstantSDKLiveStreamHelper* pLiveStreamHelper, ZoomInstantSDKLiveStreamStatus status)
{
    CString strInfo;
    switch (status)
    {
    case ZoomInstantSDKLiveStreamStatus_Connecting:
        strInfo = _T("///////Live stream is connecting.");
        break;
    case ZoomInstantSDKLiveStreamStatus_Ended:
        strInfo = _T("///////Live stream has ended.");
        break;
    case ZoomInstantSDKLiveStreamStatus_FailedTimeout:
        strInfo = _T("///////Live stream failed: Timeout.");
        break;
    case ZoomInstantSDKLiveStreamStatus_InProgress:
        strInfo = _T("///////Live stream is in progress.");
        break;
    case ZoomInstantSDKLiveStreamStatus_StartFailed:
        strInfo = _T("///////Live stream failed to start.");
        break;
    case ZoomInstantSDKLiveStreamStatus_None:
        strInfo = _T("///////Live stream status changed to none.");
        break;
    }

    OutputDebugString(strInfo);
}

void CExampleListener::onChatNewMessageNotify(IZoomInstantSDKChatHelper* pChatHelper, IZoomInstantSDKChatMessage* messageItem)
{
    if (!messageItem)
        return;

    CString strInfo;
    const zchar_t* szMessageContent = messageItem->getContent();
    IZoomInstantSDKUser* pRecievingUser = messageItem->getReceiveUser();
    IZoomInstantSDKUser* pSendingUser = messageItem->getSendUser();

    // Check if this is a public message. If false, this is a private message.
    bool bIsChatToAll = messageItem->isChatToAll();
    // Check if this message was sent from the local user.
    bool bIsSelfSend = messageItem->isSelfSend();

    time_t time = messageItem->getTimeStamp();

    if (!pSendingUser)
        return;

    strInfo.Format(_T("///////New message from %s to %s  %s"), pSendingUser->getUserName(), pRecievingUser->getUserName(), szMessageContent);
    OutputDebugString(strInfo);
}

void CExampleListener::onUserHostChanged(IZoomInstantSDKUserHelper* pUserHelper, IZoomInstantSDKUser* pUser)
{
    CString strInfo;

    const zchar_t* newHostID = pUser->getUserId();
    strInfo.Format(_T("///////The host of the session is now: userid=%s, name=%s"), newHostID, pUser->getUserName());
    OutputDebugString(strInfo);
}

void CExampleListener::onSessionNeedPassword(IZoomInstantSDKPasswordHandler* handler)
{
    // Store password handler. 
    m_pPasswordHandler = handler;

    // When ready, call inputSesstionPassword on the handler.
    if (m_pPasswordHandler)
    {
        CString strPassword;
        m_pPasswordHandler->inputSessionPassword(strPassword.GetBuffer());
    }

    // Or ignore the password request and leave the session with leaveSessionIgnorePassword.
    /* if (m_pPasswordHandler)
    {
       m_pPasswordHandler->leaveSessionIgnorePassword();
    }*/
}

void CExampleListener::onSessionPasswordWrong(IZoomInstantSDKPasswordHandler* handler)
{
    // Store password handler. 
    m_pPasswordHandler = handler;


    // When ready, call inputSesstionPassword on the handler.
    if (m_pPasswordHandler)
    {
        CString strPassword;
        m_pPasswordHandler->inputSessionPassword(strPassword.GetBuffer());
    }

    // Or ignore the password request and leave the session with leaveSessionIgnorePassword.
    /* if (m_pPasswordHandler)
    {
        m_pPasswordHandler->leaveSessionIgnorePassword();
    }*/
}

void CExampleListener::onUserManagerChanged(IZoomInstantSDKUser* pUser) {

}

void CExampleListener::onUserNameChanged(IZoomInstantSDKUser* pUser) {

}