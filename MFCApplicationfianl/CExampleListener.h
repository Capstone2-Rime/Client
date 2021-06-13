
#pragma once
//IZoomInstantSDKDelegate ���
#include "zoom_instant_sdk_delegate_interface.h"
//IZoomInstantSDK* m_pInstantSDK
#include "zoom_instant_sdk_interface.h"

#include "socket.h"
#include <fstream>
#include <iostream>
#include <thread>

using namespace std;


using namespace ZOOMINSTANTSDK;
class CExampleListener :
	public
	IZoomInstantSDKDelegate,
	IZoomInstantSDKRawDataPipeDelegate
{

public:
	//YUV
	CExampleListener();
	void Render(IZoomInstantSDKUser* pUser);
	static unsigned char* yBuffer;
	static unsigned char* uBuffer;
	static unsigned char* vBuffer;

	static int S_width;
	static int S_height;
	/*IZoomInstantSDKRawDataPipeDelegate callback functions*/
	virtual void onRawDataFrameReceived(YUVRawDataI420* data_);
	virtual void onRawDataStatusChanged(RawDataStatus status);


	//������
	CExampleListener(TCHAR word[]);



	void JoinSession(ZoomInstantSDKSessionContext* sessionContext);
	/*IZoomInstantSDKDelegat���� ��ӹ��� �޼���*/
	virtual void onSessionJoin();
	virtual void onSessionLeave();
	virtual void onError(ZoomInstantSDKErrors errorCode, int detailErrorCode);
	virtual void onUserJoin(IZoomInstantSDKUserHelper* pUserHelper, IInstantSDKVector<IZoomInstantSDKUser*>* userList);
	virtual void onUserLeave(IZoomInstantSDKUserHelper* pUserHelper, IInstantSDKVector<IZoomInstantSDKUser*>* userList);
	virtual void onUserVideoStatusChanged(IZoomInstantSDKVideoHelper* pVideoHelper, IInstantSDKVector<IZoomInstantSDKUser*>* userList);
	virtual void onUserAudioStatusChanged(IZoomInstantSDKAudioHelper* pAudioHelper, IInstantSDKVector<IZoomInstantSDKUser*>* userList);
	virtual void onUserShareStatusChanged(IZoomInstantSDKShareHelper* pShareHelper, IZoomInstantSDKUser* pUser, ZoomInstantSDKShareStatus status);
	virtual void onLiveStreamStatusChanged(IZoomInstantSDKLiveStreamHelper* pLiveStreamHelper, ZoomInstantSDKLiveStreamStatus status);
	virtual void onChatNewMessageNotify(IZoomInstantSDKChatHelper* pChatHelper, IZoomInstantSDKChatMessage* messageItem);
	virtual void onUserHostChanged(IZoomInstantSDKUserHelper* pUserHelper, IZoomInstantSDKUser* pUser);
	virtual void onUserActiveAudioChanged(IZoomInstantSDKAudioHelper* pAudioHelper, IInstantSDKVector<IZoomInstantSDKUser*>* list);
	virtual void onSessionNeedPassword(IZoomInstantSDKPasswordHandler* handler);
	virtual void onSessionPasswordWrong(IZoomInstantSDKPasswordHandler* handler);
	virtual void onUserManagerChanged(IZoomInstantSDKUser* pUser);
	virtual void onUserNameChanged(IZoomInstantSDKUser* pUser);

	/*audio raw data*/
	virtual void onMixedAudioRawDataReceived(AudioRawData* data_);
	virtual void onOneWayAudioRawDataReceived(AudioRawData* data_, IZoomInstantSDKUser* pUser);
	/*END audio raw data*/

	/*from server*/
	thread t1;
	thread t2;


private:
	IZoomInstantSDK* m_pInstantSDK;



	//session
	ZoomInstantSDKSessionContext* m_pSessionContext;
	IZoomInstantSDKSession* m_pSession;

	//connect socket
	client_socket* connect_socket;

	//file writer
	std::ofstream f;

	std::ifstream input_f;




	IZoomInstantSDKPasswordHandler* m_pPasswordHandler;
};