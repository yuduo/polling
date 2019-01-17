#pragma once
#include "stdafx.h"
#include "iNetworkInterface.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

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
	//char recvChar[1000]={0};
	//sprintf_s(recvChar,"%s",pData);//格式化输出至Str
	//string retXMLStr("<result>boolean</result>");
	//pCon->SendData((unsigned char *)retXMLStr.c_str(),strlen(retXMLStr.c_str()));

	string recXMLValueStr("");//Receive	
	string retXMLStr("");     //Result
	string tempStr="";
	try{   //Socket 传字符流/二进制流就接收什么,保持流不变
			tempStr.append((const char*)pData); //接收到的是流
			recXMLValueStr = tempStr;
			//处理XMLStr			

			/*if(NULL != xmlo)
			{
				retXMLStr = xmlo->LoadXmlMethod(recXMLValueStr);
			}*/

			
			retXMLStr="Welcom login....";
			

			pCon->SendData((unsigned char *)retXMLStr.c_str(),strlen(retXMLStr.c_str()));//发送数据->client
		}
		catch(...)
		{
			/*if (NULL != xmlo){ delete xmlo;}	*/
		}
	return 1;
}

int iNetworkInterface::OnSend(INetConnection *pCon)
{
	return 1;
}
