#pragma once
#include "stdafx.h"
#include "iNetworkInterface.h"
#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "PollDataCfg.h"
using namespace std;
#define SUPPORT_TOTOAL 8
extern const HWND GetMainHwnd();

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

	string recXMLValueStr("");//Receive	
	string retXMLStr("");     //Result
	string tempStr="";
	try{   //Socket 传字符流/二进制流就接收什么,保持流不变
			tempStr.append((const char*)pData); //接收到的是流
			recXMLValueStr = tempStr;
			//处理XMLStr			


			using json = nlohmann::json;
			auto root = json::parse(tempStr);
			//version(id，vqid阀值表)
			//计划id（计划表）

			//get current run number
			int current = 1;
			if (current<SUPPORT_TOTOAL)
			{
				PostMessage(GetMainHwnd(), WM_POLLINMIDITE, current, 0);
			}
			else {
				retXMLStr = "too much....";


				pCon->SendData((unsigned char *)retXMLStr.c_str(), strlen(retXMLStr.c_str()));//发送数据->client
			}
			
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
