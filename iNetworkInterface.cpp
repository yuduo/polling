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
	//char recvChar[1000]={0};
	//sprintf_s(recvChar,"%s",pData);//��ʽ�������Str
	//string retXMLStr("<result>boolean</result>");
	//pCon->SendData((unsigned char *)retXMLStr.c_str(),strlen(retXMLStr.c_str()));

	string recXMLValueStr("");//Receive	
	string retXMLStr("");     //Result
	string tempStr="";
	try{   //Socket ���ַ���/���������ͽ���ʲô,����������
			tempStr.append((const char*)pData); //���յ�������
			recXMLValueStr = tempStr;
			//����XMLStr			

			/*if(NULL != xmlo)
			{
				retXMLStr = xmlo->LoadXmlMethod(recXMLValueStr);
			}*/

			
			retXMLStr="Welcom login....";
			

			pCon->SendData((unsigned char *)retXMLStr.c_str(),strlen(retXMLStr.c_str()));//��������->client
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
