#include "stdafx.h"
#include "PollFunction.h"

#include <iostream>


CPollFunction::CPollFunction()
{
	m_hThread= INVALID_HANDLE_VALUE;
	m_bIsPolling=false;
	m_nPollIndex=0;
	m_bIsRuning = false;
}


CPollFunction::~CPollFunction()
{
	StopPoll();
}

bool CPollFunction::StartPoll()
{
	if (m_bIsPolling)
	{
		return false;
	}

	if (m_tCurSelPlan.strPlanName.size() <= 0)
	{
		return false;
	}
	if (m_tCurSelPlan.lstDevice.size() <= 0)
	{
		return false;
	}
	if (m_tCurSelPlan.strTimeList.size() <= 0)
	{
		return false;
	}

	//z test 0929 ���ӣ���Ҫ���ʼ������ֿ�ʼʱ�䣬����ʱ��
	CTime ct = CTime::GetCurrentTime(); //��ȡ��ǰʱ��
	CString str = ct.Format("%Y-%m_%d %H-%M-%S");//��ʽ��ʱ��
	m_strTrunBegTime = str.GetBuffer(0);
	

	m_bIsRuning = true;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadPollFunc, this, 0, 0);
	if (INVALID_HANDLE_VALUE != m_hThread)
	{
		m_bIsPolling = true;
	}
	else
	{
		m_bIsPolling = false;
		m_bIsRuning = false;
	}
	return m_bIsPolling;
}

bool CPollFunction::StopPoll()
{
	m_bIsRuning = false;
	m_bIsPolling = false;
	cOneTurn.StopPoll();
	return true;
}


bool CPollFunction::GetPollStatus()
{
	return m_bIsPolling;
}

bool CPollFunction::GetRunStatus()
{
	return m_bIsRuning;
}

void CPollFunction::SetPollPlan(PLANINFO  tplan)
{
	m_tCurSelPlan = tplan;
}

PLANINFO CPollFunction::GetPollPlan()
{
	return m_tCurSelPlan;
}


void  CPollFunction::SetSavePath(std::string strPath)
{
	m_strSavePath = strPath;
}

void  CPollFunction::UpdateRunStatus(bool bRun)
{
	m_bIsRuning = bRun;
	if (m_bIsRuning == false)
	{
		m_bIsPolling = false;
	}
}

time_t CPollFunction::StringToDatetime(std::string str)
{
	char *cha = (char*)str.data();             // ��stringת����char*��
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	tm tm_t;                                    // ����tm�ṹ�塣
	int  hour=0, minute=0, second=0;// ����ʱ��ĸ���int��ʱ������
	sscanf(cha, "%d:%d:%d", &hour, &minute, &second);// ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
	tm_t.tm_year = sys.wYear - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��
	tm_t.tm_mon = sys.wMonth - 1;                    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
	tm_t.tm_mday = sys.wDay;                         // �ա�
	if (hour >= 0 && hour < 24)
	{
		tm_t.tm_hour = hour;                        // ʱ��
	}
	else
	{
		tm_t.tm_hour = 0;
	}
	
	if (minute >= 0 && minute < 60)
	{
		tm_t.tm_min = minute;                       // �֡�
	}
	else
	{
		tm_t.tm_min = 0;
	}

	if (second >= 0 && second < 60)
	{
		tm_t.tm_sec = second;                       // �롣
	}
	else
	{
		tm_t.tm_sec = 0;
	}
	
	tm_t.tm_isdst = 0;                          // ������ʱ��
	time_t t = mktime(&tm_t);                  // ��tm�ṹ��ת����time_t��ʽ��
	return t;                                 // ����ֵ�� 
}

bool CPollFunction::InInvalidTime(std::string strBeg,std::string strEnd)
{
	
	if (strBeg == "" || strEnd == "")
	{
		return false;
	}
	time_t tbeg = StringToDatetime(strBeg);
	time_t tend = StringToDatetime(strEnd);
	time_t t_Now = time(0);
	struct tm* tm_Now = localtime(&t_Now);
	time_t tNow = mktime(tm_Now);
	if (tbeg <= tNow && tNow <= tend)
	{
		//poll
		return true;
	}
	return false;
}

int  CPollFunction::JudgeAndStart()
{
	//���������ж��Ƿ���Ҫ��ѵ
	if (cOneTurn.GetPollStatus())
	{
		if (GetRunStatus()==false)
		{
			cOneTurn.StopPoll();
		}
		return 3;
	}
	time_t t_Now = time(0);
	struct tm* tm_Now = localtime(&t_Now);
	time_t r = mktime(tm_Now);

	bool bNeed = false;
	time_t tbeg;
	time_t tend;
	time_t tMaxTime=0;

	std::list<std::string>::iterator itTimList = m_tCurSelPlan.strTimeList.begin();
	for (;itTimList != m_tCurSelPlan.strTimeList.end();itTimList++)
	{
		std::string strBeg = "";
		std::string strEnd = "";
		std::size_t tfound = (*itTimList).find(",");
		if (tfound != std::string::npos)
		{
			strBeg = (*itTimList).substr(0, tfound);
			strEnd = (*itTimList).substr(tfound + 1);
		}
		if (strBeg == "" && strEnd == "")
		{
			continue;
		}
		tbeg = StringToDatetime(strBeg);
		tend = StringToDatetime(strEnd);
		if (tMaxTime < tend)
		{
			tMaxTime = tend;
		}
		if (tbeg <= r && r <= tend)
		{
			//poll
			bNeed = true;
			break;
		}
	}

	if (!bNeed)
	{
		if (tMaxTime < r)  //�����Ѿ�����
		{
			m_bIsRuning = false;
			
			
			

		}
		return 2;
	}
	else
	{
		if (GetRunStatus())
		{
			cOneTurn.InitData(m_tCurSelPlan.strPlanName, tbeg, tend, m_tCurSelPlan.lstDevice, m_tCurSelPlan.wInterval, m_tCurSelPlan.wVidCount);
			cOneTurn.StartPoll();
		}
	}
	return 0;
}


void CPollFunction::SendWarningMail()
{
	
}
unsigned int CPollFunction::ThreadPollFunc(void *pParam)
{
	CPollFunction* pThis = (CPollFunction*)pParam;
	if (pThis)
	{
		while (pThis->GetRunStatus())
		{
			Sleep(1000);

			pThis->JudgeAndStart();

		}
	
	}
	return 0;
}

///////////////
COneTurnPoll::COneTurnPoll()
{
	m_hThread = INVALID_HANDLE_VALUE;
	m_nPollIndex = 0;
	m_bIsRuning = false;
}


COneTurnPoll::~COneTurnPoll()
{
	StopPoll();
}

bool COneTurnPoll::StartPoll()
{
	if (m_strPlanName.size() <= 0)
	{
		return false;
	}
	if (m_lstPos.size() <= 0)
	{
		return false;
	}
	

	m_bIsRuning = true;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadPollFunc, this, 0, 0);
	if (INVALID_HANDLE_VALUE != m_hThread)
	{
		m_bIsRuning = true;
	}
	else
	{
		m_bIsRuning = false;
	}
	return m_bIsRuning;
}
bool COneTurnPoll::StopPoll()
{
	m_bIsRuning = false;
	return true;
}
bool COneTurnPoll::GetPollStatus()
{
	return m_bIsRuning;
}

int COneTurnPoll::GetInterval()
{
	return m_nInterVal;
}

void COneTurnPoll::InitData(std::string strPlan, time_t tBeg, time_t tEnd, std::list<tagPosInfo>lstDev, int nIntv, int nVdCount)
{
	m_strPlanName= strPlan;
	m_lstPos= lstDev;
	m_tStart= tBeg;
	m_tEnd= tEnd;
	m_nInterVal= nIntv;
	m_nVdCount= nVdCount;
	m_nPollIndex = 0;
}


int COneTurnPoll::StartATurn()
{
	time_t t_Now = time(0);
	struct tm* tm_Now = localtime(&t_Now);
	time_t r = mktime(tm_Now);
	if (m_tStart > r || r > m_tEnd)
	{
		m_bIsRuning = false;
		return 1;
	}

	//��ʼ����
	//
	
	m_nPollIndex = m_nPollIndex + m_nVdCount;
	
	if (m_nPollIndex >= m_lstPos.size())
	{
		m_nPollIndex = 0;
	}

	return 0;
}


int COneTurnPoll::StartASnapTurn()
{
	

	//��ʼ����
	//
	

	return 0;
}


unsigned int COneTurnPoll::ThreadPollFunc(void *pParam)
{
	COneTurnPoll* pThis = (COneTurnPoll*)pParam;
	if (pThis)
	{
		int nNum = 0;
		bool nFirtSnap = false;
		while (pThis->GetPollStatus())
		{
			Sleep(1000);
			if (!pThis->GetPollStatus())
			{
				break;
			}
			nNum++;
			if (pThis->GetInterval() < nNum+1)
			{
				if (nFirtSnap == false)
				{

					pThis->StartASnapTurn();
					nFirtSnap = true;
				}
			}
			if (pThis->GetInterval() < nNum)
			{
				nNum = 0;
				//��ʼһ������
				pThis->StartATurn();
				nFirtSnap = false;
			}
		}
	}
	return 0;
}


