#pragma once
#include "NetworkInterface.h"
#pragma comment(lib,"NetworkModule.lib")

class iNetworkInterface: public INetAcceptorSink,public INetConnectionSink
{
public:
	iNetworkInterface();
	~iNetworkInterface(void);


public:

	 int OnConnect(int nReason, INetConnection *pCon);
	 int OnDisconnect(int nReason, INetConnection *pCon);
	 int OnReceive(unsigned char *pData, int nLen, INetConnection *pCon);
     int OnSend(INetConnection *pCon);
	 int OnConnectIndication(INetConnection *pCon, INetAcceptor *pApt);

	 int iNetworkInterface::StartListen(unsigned short wPort, unsigned long dwLocalAddr = 0/*INADDR_ANY*/);

	 int iNetworkInterface::StopListen();
	 int iNetworkInterface::GetType();
	//virtual int OnCommand(unsigned char *pData, int nLen, INetConnection *pCon){return 0;}
	//virtual ~INetConnectionSink(){}

//
private:
	//XMLInfoClass* xmlo;//÷∏’Î:¥¶¿ÌXML
	//CUI_Main* cmdXMLPointer;
};

