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
	  //释放指针
	//if (NULL != xmlo)
	//{
	//	delete xmlo;
	//}
}

int iNetworkInterface::OnConnectIndication(INetConnection *pCon, INetAcceptor *pApt)
{
	//得到客户端连接的CONNECT
	if(NULL == pCon)
	{
		//return error code
		return -1;
	}	
	//设置会话的回调
	pCon->SetSink(this);
	//将该会话存储起来	

	return 1;
}


//连接成功后开始触发
int iNetworkInterface::OnConnect(int nReason, INetConnection *pCon)
{	
	//Clent端：Socket连接成功后发生
	try
	{   
	}
	catch(...)
	{
	}
	return 1;
}

//Clent端Socket断开后触发
int iNetworkInterface::OnDisconnect(int nReason, INetConnection *pCon)
{
	NetworkDestroyConnection(pCon);
	return 1;
}

//接收Client数据
int iNetworkInterface::OnReceive(unsigned char *pData, int nLen, INetConnection *pCon)
{

	string retXMLStr("");     //Result
	string tempStr="";
	
	tempStr.append((const char*)pData); //接收到的是流
			


	using json = nlohmann::json;
	auto root = json::parse(tempStr);
	//version(id，vqid阀值表)
	//计划id（计划表）
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
		
		std::string str1 = "成功";
		;
		j["message"] = base64_encode(reinterpret_cast<const unsigned char*>(str1.c_str()), str1.length());
		j["code"] = 0;
		PostMessage(GetMainHwnd(), WM_POLLINMIDITE, 0, (LPARAM)(LPCTSTR)planId.c_str());
	}
	else {
		retXMLStr = "";
		std::string str1 = "服务器忙";
		j["success"] = 1;
		j["message"] = base64_encode(reinterpret_cast<const unsigned char*>(str1.c_str()), str1.length());
		j["code"] = 1001;
		
	}
	try {   //Socket 传字符流/二进制流就接收什么,保持流不变
		std::string temp = j.dump();
			pCon->SendData((unsigned char *)j.dump().c_str(), strlen(j.dump().c_str()));//发送数据->client
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
