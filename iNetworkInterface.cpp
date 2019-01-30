#pragma once
#include "stdafx.h"
#include "iNetworkInterface.h"

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "PollDataCfg.h"
#include "base64.h"
using namespace std;
#define SUPPORT_TOTOAL 8
extern const HWND GetMainHwnd();
extern const int GetSession();
iNetworkInterface::iNetworkInterface()
{
	//xmlo = NULL;
	//CI_Main  xmlo = new XMLInfoClass();
	//cmdXMLPointer=cmp;

	
}

iNetworkInterface::~iNetworkInterface(void)
{
	  //�ͷ�ָ��
	//if (NULL != xmlo)
	//{
	//	delete xmlo;
	//}
}

int iNetworkInterface::OnConnectIndication(INetConnection *pCon, INetAcceptor *pApt)
{
	//�õ��ͻ������ӵ�CONNECT
	if(NULL == pCon)
	{
		//return error code
		return -1;
	}	
	//���ûỰ�Ļص�
	pCon->SetSink(this);
	//���ûỰ�洢����	

	return 1;
}


//���ӳɹ���ʼ����
int iNetworkInterface::OnConnect(int nReason, INetConnection *pCon)
{	
	//Clent�ˣ�Socket���ӳɹ�����
	try
	{   
	}
	catch(...)
	{
	}
	return 1;
}

//Clent��Socket�Ͽ��󴥷�
int iNetworkInterface::OnDisconnect(int nReason, INetConnection *pCon)
{
	NetworkDestroyConnection(pCon);
	return 1;
}

//����Client����
int iNetworkInterface::OnReceive(unsigned char *pData, int nLen, INetConnection *pCon)
{

	string retXMLStr("");     //Result
	string tempStr="";
	
	tempStr.append((const char*)pData); //���յ�������
			


	using json = nlohmann::json;
	auto root = json::parse(tempStr);
	//version(id��vqid��ֵ��)
	//�ƻ�id���ƻ���
	this->planId=root["planId"];
	//get current run number
	int current = GetSession();
	json j;
	if (current<SUPPORT_TOTOAL)
	{
		j["success"] = 0;
		BYTE byte[4];
		byte[0] = 0xb3;
		byte[1] = 0xc9;
		byte[2] = 0xb9;
		byte[3] = 0xa6;
		
		std::string str1 = "�ɹ�";
		;
		j["message"] = base64_encode(reinterpret_cast<const unsigned char*>(str1.c_str()), str1.length());
		j["code"] = 0;
		PostMessage(GetMainHwnd(), WM_POLLINMIDITE, 0, (LPARAM)(LPCTSTR)planId.c_str());
	}
	else {
		retXMLStr = "";
		std::string str1 = "������æ";
		j["success"] = 1;
		j["message"] = base64_encode(reinterpret_cast<const unsigned char*>(str1.c_str()), str1.length());
		j["code"] = 1001;
		
	}
	try {   //Socket ���ַ���/���������ͽ���ʲô,����������
		std::string temp = j.dump();
			pCon->SendData((unsigned char *)j.dump().c_str(), strlen(j.dump().c_str()));//��������->client
		}
		catch(...)
		{
			
		}		
		
	return 1;
}

int iNetworkInterface::OnSend(INetConnection *pCon)
{
	return 1;
}
