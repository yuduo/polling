#pragma once
#include "PollDataCfg.h"


class COneTurnPoll
{
public:
	COneTurnPoll();
	~COneTurnPoll();
public:
	static unsigned int __stdcall ThreadPollFunc(void *pParam);
	bool StartPoll();
	bool StopPoll();
	bool GetPollStatus();
	int GetInterval();
	void InitData(std::string strPlan, time_t tBeg, time_t tEnd, std::list<tagPosInfo>lstDev, int nIntv, int nVdCount);
	int StartASnapTurn();
	
private:
	std::string m_strPlanName;
	std::list<tagPosInfo> m_lstPos;
	time_t m_tStart;
	time_t m_tEnd;
	int m_nInterVal;
	int m_nVdCount;

	HANDLE      m_hThread;
	bool        m_bIsRuning;

	int         m_nPollIndex;
	int         m_nDelay;

	std::string m_strSavePath;

	int StartATurn();

};

class CPollFunction
{
public:
	CPollFunction();
	~CPollFunction();
public:
	static unsigned int __stdcall ThreadPollFunc(void *pParam);
	bool StartPoll();
	bool StopPoll();
	bool GetPollStatus();
	bool GetRunStatus();
	void SetPollPlan(PLANINFO  tplan);
	PLANINFO GetPollPlan();
	void SetSavePath(std::string strPath);
	void  UpdateRunStatus(bool bRun);
	int  JudgeAndStart();
	void StartImmediate();
private:
	PLANINFO    m_tCurSelPlan;
	HANDLE      m_hThread;
	bool        m_bIsRuning;
	bool        m_bIsPolling;
	int         m_nPollIndex;
	std::string m_strSavePath;

	std::string m_strTrunBegTime; //z test 0929 增加，需要在邮件中体现开始时间，结束时间


	COneTurnPoll cOneTurn;

	//void WritePollLog(string strLog, string strName);
	time_t StringToDatetime(std::string str);
	bool InInvalidTime(std::string strBeg, std::string strEnd);
	void DeleteCurrentPlan(PLANINFO curPlan);
	void SendWarningMail();

};



