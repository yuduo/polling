
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "tinyxml2.h"
#include "MySQLDB.h"
#include "PollDataCfg.h"
#include "IVQSModule.h"

#define PLAN_COUNT 1
#define PLAN_STATUS_NULL 1
#define PLAN_STATUS_RUNNING 2
#define PLAN_STATUS_DONE 3
#pragma comment(lib,"VQSModule.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
HWND				CMFCApplication1Dlg::m_hOwner;
int CMFCApplication1Dlg::m_immediteSession;
const HWND GetMainHwnd()
{
	return CMFCApplication1Dlg::m_hOwner;
}
const int GetSession()
{
	return CMFCApplication1Dlg::m_immediteSession;
}
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg �Ի���



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAYERCTRL1, m_player1);
	DDX_Control(pDX, IDC_PLAYERCTRL2, m_player2);
	DDX_Control(pDX, IDC_PLAYERCTRL3, m_player3);
	DDX_Control(pDX, IDC_PLAYERCTRL4, m_player4);
	DDX_Control(pDX, IDC_PLAYERCTRL5, m_player5);
	DDX_Control(pDX, IDC_PLAYERCTRL6, m_player6);
	DDX_Control(pDX, IDC_WORKSPACECTRL1, m_workspace);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_MESSAGE(WM_POLLSNAPVIDEO, ShowSnapPoll)
	ON_MESSAGE(WM_UPDATESNAPINFO, PollMessageHandle)
	ON_MESSAGE(WM_POLLINMIDITE, PollImmidate)
	ON_MESSAGE(WM_POLLNEXTPLAN, PollNextPlan)
	
	
END_MESSAGE_MAP()
unsigned int CMFCApplication1Dlg::ThreadPollImmediate(void *pParam)
{
	CMFCApplication1Dlg* pThis = (CMFCApplication1Dlg*)pParam;
	m_immediteSession++;
	//xml
	tinyxml2::XMLDocument doc;
	doc.LoadFile("c:\\setting.xml");
	const char* Address = doc.FirstChildElement("mysql")->FirstChildElement("Address")->GetText();
	const char* Port = doc.FirstChildElement("mysql")->FirstChildElement("Port")->GetText();
	const char* user = doc.FirstChildElement("mysql")->FirstChildElement("user")->GetText();
	const char* password = doc.FirstChildElement("mysql")->FirstChildElement("password")->GetText();

	//mysql
	MySQLDB m_DBDriver;
	//���ݿ�����
	if (!m_DBDriver.Connect(_T(Address), 3306, _T("zhyw"), _T(user), _T(password)))
	{
		m_DBDriver.Disconnect();
		return 0;
	}
	if (!m_DBDriver.CheckDB())
	{
		return 0;
	}
	else
	{
		try
		{

			//����SQL���
			std::string setchar = "set charset utf8;";
			//ִ�в�ѯ
			m_DBDriver.SQLExecute(setchar);

			//����SQL���
			std::string strSql = "SELECT *  FROM vqdplan  left join monvqd on vqdplan.ID=monvqd.VQD_ID where vqdplan.ID=" + pThis->m_planid;
			//ִ�в�ѯ

			MySQLResultSet logRecord;
			m_DBDriver.SQLQuery(strSql, logRecord);
			int nRowCount = (int)logRecord.size();
			if (!nRowCount)return 0;
			for (int i = 0; i < nRowCount; i++)
			{
				PLANINFO plan;
				plan.InitData();

				plan.strPlanName = logRecord[i]["COL_PLAN_NAME"];
				tagPosInfo tag;
				tag.strPosID = logRecord[i]["MON_ID"];
				plan.lstDevice.push_back(tag);
				//��ʼ����
				pThis->OpenVideo(logRecord[i]["MON_ID"], m_immediteSession);
				Sleep(10000);
				pThis->AnalysisOne(logRecord[i]["MON_ID"], m_immediteSession);
				pThis->Stop(m_immediteSession);
			}

		}
		catch (...)
		{

		}
	}
	m_immediteSession--;
	m_DBDriver.Disconnect();
	return 0;
}
LRESULT CMFCApplication1Dlg::PollImmidate(WPARAM wParam, LPARAM lParam)
{
	//plan id
	LPCTSTR l = (LPCTSTR)lParam;
	char *p = (char*)lParam;
	m_planid = "2";
	

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadPollImmediate, this, 0, 0);


	

	return 0;
}
void CMFCApplication1Dlg::AnalysisOne(std::string strPosID, int nscount)
{
	std::string strPat = "";
	sprintf((char*)strPat.c_str(), "%s\\%s", "f:", "temp");
	//��ͼ������Ӧ��Ŀ¼��
	SYSTEMTIME sm;
	GetLocalTime(&sm);
	char strFilePath[100];


	sprintf((char*)strFilePath, _T("%s/%s_%d%02d%02d_%02d%02d%02d.jpg"), strPat.c_str(), strPosID.c_str(),
		sm.wYear, sm.wMonth, sm.wDay,
		sm.wHour, sm.wMinute, sm.wSecond);

	SaveSnapImage(nscount, strFilePath);
	RESULT_VALUE lpResultOut;
	if (VQS_API_GetVQSResult(strFilePath, &lpResultOut))
	{
		//�������ݿ�
		//xml
		tinyxml2::XMLDocument doc;
		doc.LoadFile("c:\\setting.xml");
		const char* Address = doc.FirstChildElement("mysql")->FirstChildElement("Address")->GetText();
		const char* Port = doc.FirstChildElement("mysql")->FirstChildElement("Port")->GetText();
		const char* user = doc.FirstChildElement("mysql")->FirstChildElement("user")->GetText();
		const char* password = doc.FirstChildElement("mysql")->FirstChildElement("password")->GetText();

		//mysql
		MySQLDB m_DBDriver;
		//���ݿ�����
		if (!m_DBDriver.Connect(_T(Address), 3306, _T("zhyw"), _T(user), _T(password)))
		{
			m_DBDriver.Disconnect();
			return ;
		}
		if (!m_DBDriver.CheckDB())
		{
			return ;
		}
		else
		{
			try
			{

				//����SQL���
				std::string setchar = "set charset utf8;";
				//ִ�в�ѯ
				m_DBDriver.SQLExecute(setchar);

				//����SQL���
				std::string strSql = "insert into videodiagnosis (IMAGE_BIAS,IMAGE_BLUR,IMAGE_OVERLIGHTING,NOISE_DISTURB,FRINGE_DISTURB,YUNTAI_ANOMALY,PICTURE_FREEZE,SIGNAL_LOSS) values('";
				strSql += lpResultOut.bytColorCastValue;
				strSql += "','";
				strSql += lpResultOut.bytClarityValue;
				strSql += "','";
				strSql += lpResultOut.bytBrightValue;
				strSql += "','";
				strSql += lpResultOut.bytNoiseValue;
				strSql += "','";
				strSql += lpResultOut.bytWaveValue;
				strSql += "','";
				strSql += lpResultOut.bytMovedValue;
				strSql += "','";
				strSql += lpResultOut.bytFreezeValue;
				strSql += "','";
				strSql += lpResultOut.bytSignalValue + "')";
				//ִ�в�ѯ

				MySQLResultSet logRecord;
				m_DBDriver.SQLQuery(strSql, logRecord);

			}
			catch (...)
			{

			}
		}
		m_DBDriver.Disconnect();
	}
}
BOOL CMFCApplication1Dlg::SaveSnapImage(int index,std::string strFilePath)
{
	
	switch (index)
	{
	case 0:
		m_player1.DoSnapPicture(strFilePath.c_str(), 0);
		break;
	case 1:
		m_player2.DoSnapPicture(strFilePath.c_str(), 0);
		break;
	case 2:
		m_player3.DoSnapPicture(strFilePath.c_str(), 0);
		break;
	case 3:
		m_player4.DoSnapPicture(strFilePath.c_str(), 0);
		break;
	case 4:
		m_player5.DoSnapPicture(strFilePath.c_str(), 0);
		break;
	case 5:
		m_player6.DoSnapPicture(strFilePath.c_str(), 0);
		break;
	default:
		break;
	}

	return false;
}
LRESULT CMFCApplication1Dlg::PollMessageHandle(WPARAM wParam, LPARAM lParam)
{

	bool bBreak = true;

	int nIndex = LOWORD(wParam);
	int nCount = 1;
	char *p = (char*)lParam;
	PLANINFO m_tCurPlanInfo = getPlanInfo(p);
	int nind = nIndex - nCount;
	if (nind < 0)
	{
		nind = 0;
	}
	int nscount = 0;
	std::list<tagPosInfo>::iterator itDmList = m_tCurPlanInfo.lstDevice.begin();
	//û��ץ�ı�־����ץ��
	/*if (m_tCurPlanInfo.wSnapFlag != 1)
	{
		return 1;
	}*/

	for (; itDmList != m_tCurPlanInfo.lstDevice.end(); itDmList++)
	{
		if (nIndex > nind)
		{
			nind++;
			continue;
		}
		if (nscount < nCount)
		{
			std::string strPat = "";
			sprintf((char*)strPat.c_str(), "%s\\%s\\", "f:", "temp");
			//��ͼ������Ӧ��Ŀ¼��
			SYSTEMTIME sm;
			GetLocalTime(&sm);
			char strFilePath[100];


			sprintf((char*)strFilePath, _T("%s/%s_%d%02d%02d_%02d%02d%02d.jpg"), strPat.c_str(), itDmList->strPosID.c_str(),
				sm.wYear, sm.wMonth, sm.wDay,
				sm.wHour, sm.wMinute, sm.wSecond);
			
			SaveSnapImage(nscount, strFilePath);
			RESULT_VALUE lpResultOut;
			if(VQS_API_GetVQSResult(strFilePath,&lpResultOut))
			{
				//�������ݿ�
				//xml
				tinyxml2::XMLDocument doc;
				doc.LoadFile("c:\\setting.xml");
				const char* Address = doc.FirstChildElement("mysql")->FirstChildElement("Address")->GetText();
				const char* Port = doc.FirstChildElement("mysql")->FirstChildElement("Port")->GetText();
				const char* user = doc.FirstChildElement("mysql")->FirstChildElement("user")->GetText();
				const char* password = doc.FirstChildElement("mysql")->FirstChildElement("password")->GetText();

				//mysql
				MySQLDB m_DBDriver;
				//���ݿ�����
				if (!m_DBDriver.Connect(_T(Address), 3306, _T("zhyw"), _T(user), _T(password)))
				{
					m_DBDriver.Disconnect();
					return 0;
				}
				if (!m_DBDriver.CheckDB())
				{
					return 0;
				}
				else
				{
					try
					{

						//����SQL���
						std::string setchar = "set charset utf8;";
						//ִ�в�ѯ
						m_DBDriver.SQLExecute(setchar);

						//����SQL���
						std::string strSql = "insert into videodiagnosis (IMAGE_BIAS,IMAGE_BLUR,IMAGE_OVERLIGHTING,NOISE_DISTURB,FRINGE_DISTURB,YUNTAI_ANOMALY,PICTURE_FREEZE,SIGNAL_LOSS) values('";
						strSql += lpResultOut.bytColorCastValue;
						strSql += "','";
						strSql +=lpResultOut.bytClarityValue;
						strSql += "','";
						strSql += lpResultOut.bytBrightValue;
						strSql += "','";
						strSql += lpResultOut.bytNoiseValue;
						strSql += "','";
						strSql += lpResultOut.bytWaveValue;
						strSql += "','";
						strSql += lpResultOut.bytMovedValue;
						strSql += "','";
						strSql += lpResultOut.bytFreezeValue;
						strSql += "','";
						strSql += lpResultOut.bytSignalValue + "')";
						//ִ�в�ѯ

						MySQLResultSet logRecord;
						m_DBDriver.SQLQuery(strSql, logRecord);
						
					}
					catch (...)
					{

					}
				}
				m_DBDriver.Disconnect();
			}
			nscount++;
		}
		else
		{
			break;
		}

		nind++;
	}


	return 0;
}

void CMFCApplication1Dlg::Stop(int index) {
	switch (index)
	{
	case 0:
		m_player1.Stop();
		break;
	case 1:
		m_player2.Stop();
		break;
	case 2:
		m_player3.Stop();
		break;
	case 3:
		m_player4.Stop();
		break;
	case 4:
		m_player5.Stop();
		break;
	case 5:
		m_player6.Stop();
		break;
	default:
		break;
	}
}
BOOL CMFCApplication1Dlg::OpenVideo(std::string strPosID,int index)
{
	CString strmode = "<?xml version=\"1.0\"?> \
		<InviteConfig> \
		<TransParam TransMode=\"TCP-C\" StreamCBMode=\"\" /> \
		<VideoParam Codec=\"2\" Resolution=\"4\" Fps=\"25\" BRMode=\"1\" Kbps=\"2000\" Enbale=\"1\" />\
		</InviteConfig> ";

	if (strPosID == "") {
		return false;
	}
	
	switch (index)
	{
	case 0:
		m_player1.Invite(strPosID.c_str(), "", strmode);
		break;
	case 1:
		m_player2.Invite(strPosID.c_str(), "", strmode);
		break;
	case 2:
		m_player3.Invite(strPosID.c_str(), "", strmode);
		break;
	case 3:
		m_player4.Invite(strPosID.c_str(), "", strmode);
		break;
	case 4:
		m_player5.Invite(strPosID.c_str(), "", strmode);
		break;
	case 5:
		m_player6.Invite(strPosID.c_str(), "", strmode);
		break;

	default:
		break;
	}
	return true;
}
PLANINFO CMFCApplication1Dlg::getPlanInfo(std::string strID)
{
	std::list<PLANINFO>::iterator itList = m_planList.begin();
	for (; itList != m_planList.end(); itList++)
	{
		if (itList->strPlanID == strID)
		{
			return *itList;
		}
	}
	return *itList;
}
LRESULT  CMFCApplication1Dlg::ShowSnapPoll(WPARAM wParam, LPARAM lParam)
{
	int nIndex = LOWORD(wParam);
	int nCount = 1;
	char *p = (char*)lParam;
	PLANINFO m_tCurPlanInfo = getPlanInfo(p);
	int nind = 0;
	int nscount = 0;
	//��ֹͣ��һ�ֵĻ���
	for (int nStindex = 0; nStindex < nCount; nStindex++)
	{
		Stop(nStindex);
	}

	std::list<tagPosInfo>::iterator itDmList = m_tCurPlanInfo.lstDevice.begin();
	for (; itDmList != m_tCurPlanInfo.lstDevice.end(); itDmList++)
	{
		if (nIndex > nind)
		{
			nind++;
			continue;
		}
		if (nscount < nCount)
		{
			
			//��ʼ����
			OpenVideo(itDmList->strPosID.c_str(), nscount);

			nscount++;
		}
		else
		{
			
			break;
		}

		nind++;
	}
	return 1;
}
// CMFCApplication1Dlg ��Ϣ�������
//#include "json.hpp"
BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//using json = nlohmann::json;
	//auto root = json::parse("{\"planId\": \"2\"}");
	////version(id��vqid��ֵ��)
	////�ƻ�id���ƻ���
	//int planId = root["planId"];

	m_hOwner = m_hWnd;
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	LPUNKNOWN  lpunknown = m_workspace.GetControlUnknown();
	LPDISPATCH lpdisp = NULL;
	lpunknown->QueryInterface(IID_IDispatch,(void**)&lpdisp);

	//xml
	tinyxml2::XMLDocument doc;
	doc.LoadFile("c:\\setting.xml");
	const char* Address = doc.FirstChildElement("mysql")->FirstChildElement("Address")->GetText();
	const char* Port = doc.FirstChildElement("mysql")->FirstChildElement("Port")->GetText();
	const char* user = doc.FirstChildElement("mysql")->FirstChildElement("user")->GetText();
	const char* password = doc.FirstChildElement("mysql")->FirstChildElement("password")->GetText();

	const char* localip = doc.FirstChildElement("local")->FirstChildElement("ipaddress")->GetText();
	const char* localnat = doc.FirstChildElement("local")->FirstChildElement("nataddress")->GetText();
	//mysql
	MySQLDB m_DBDriver;
	//���ݿ�����
	if (!m_DBDriver.Connect(_T(Address), 3306, _T("zhyw"), _T(user), _T(password)))
	{
		m_DBDriver.Disconnect();
		return 0;
	}
	if (!m_DBDriver.CheckDB())
	{
		return 0;
	}
	else
	{
		try
		{

			//����SQL���
			std::string setchar = "set charset utf8;";
			//ִ�в�ѯ
			m_DBDriver.SQLExecute(setchar);

			//����SQL���
			std::string strSql = "SELECT *  FROM vqdplan  left join monvqd on vqdplan.ID=monvqd.VQD_ID left join collector on vqdplan.COLLECTOR_ID=collector.ID where DIA_TIME=1 and STATUS=0  AND IP_ADDRESS='" + std::string(localip) + "' or IP_ADDRESS='" + std::string(localnat) + "'";
			//ִ�в�ѯ

			MySQLResultSet logRecord;
			m_DBDriver.SQLQuery(strSql, logRecord);
			int nRowCount = (int)logRecord.size();
			if (!nRowCount)return 0;
			for (int i = 0; i < nRowCount; i++)
			{
				PLANINFO plan;
				plan.InitData();
				if (logRecord[i]["COL_INTERVAL"]=="") {
					plan.wInterval = 60;
				}else
					plan.wInterval = atol(logRecord[i]["COL_INTERVAL"].c_str());
				plan.strPlanName = logRecord[i]["COL_PLAN_NAME"];
				plan.strPlanID= logRecord[i]["ID"];
				tagPosInfo tag;
				tag.strPosID= logRecord[i]["MON_ID"];
				plan.lstDevice.push_back(tag);
				plan.wVidCount = PLAN_COUNT;
				if (logRecord[i]["MONDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["MONDAY"]);
				}
				if (logRecord[i]["TUESDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["TUESDAY"]);
				}
				if (logRecord[i]["WEDNESDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["WEDNESDAY"]);
				}
				if (logRecord[i]["THURSDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["THURSDAY"]);
				}
				if (logRecord[i]["FRIDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["FRIDAY"]);
				}
				if (logRecord[i]["SATURDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["SATURDAY"]);
				}
				if (logRecord[i]["SUNDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["SUNDAY"]);
				}
				m_planList.push_back(plan);
				
			}
			if (m_planList.size() > 0)
			{
				auto it = m_planList.begin();
				m_pollFun.SetPollPlan(*it);
				
				m_pollFun.m_strID=((PLANINFO)*it).strPlanID;
				m_pollFun.StartPoll();
				
			}
			if (m_planList.size() > 1)
			{
				auto it = m_planList.begin();
				it = std::next(it, 1);
				m_pollFun1.SetPollPlan(*it);
				
				m_pollFun1.m_strID = ((PLANINFO)*it).strPlanID;
				m_pollFun1.StartPoll();

			}
		}
		catch (...)
		{

		}
	}
	m_DBDriver.Disconnect();

	NetworkInit();
	iNetworkInterface *p_iNetInface = new iNetworkInterface();
	p_TcpAcceptor = CreateRawTcpAcceptor(p_iNetInface);
	

	m_workspace.InitNew("admin","123456","122.112.203.74",8083);

	m_player1.ConnectToWorkspace(lpdisp);//
	m_player2.ConnectToWorkspace(lpdisp);
	m_player3.ConnectToWorkspace(lpdisp);
	m_player4.ConnectToWorkspace(lpdisp);
	m_player5.ConnectToWorkspace(lpdisp);
	m_player6.ConnectToWorkspace(lpdisp);

	p_TcpAcceptor->StartListen(2000);//�����˿�/hostIP(Ĭ��ȫ������)
	m_immediteSession = 0;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CMFCApplication1Dlg::UpdatePlanStatus(std::string strID, int type) {
	//xml
	tinyxml2::XMLDocument doc;
	doc.LoadFile("c:\\setting.xml");
	const char* Address = doc.FirstChildElement("mysql")->FirstChildElement("Address")->GetText();
	const char* Port = doc.FirstChildElement("mysql")->FirstChildElement("Port")->GetText();
	const char* user = doc.FirstChildElement("mysql")->FirstChildElement("user")->GetText();
	const char* password = doc.FirstChildElement("mysql")->FirstChildElement("password")->GetText();

	const char* localip = doc.FirstChildElement("local")->FirstChildElement("ipaddress")->GetText();
	const char* localnat = doc.FirstChildElement("local")->FirstChildElement("nataddress")->GetText();
	//mysql
	MySQLDB m_DBDriver;
	//���ݿ�����
	if (!m_DBDriver.Connect(_T(Address), 3306, _T("zhyw"), _T(user), _T(password)))
	{
		m_DBDriver.Disconnect();
		return;
	}
	if (!m_DBDriver.CheckDB())
	{
		return;
	}
	else
	{
		try
		{

			//����SQL���
			std::string setchar = "set charset utf8;";
			//ִ�в�ѯ
			m_DBDriver.SQLExecute(setchar);

			//����SQL���
			std::string strSql = "update vqdplan set STATUS=" + std::string(type,1) + "where ID='" + strID + "'";
			//ִ�в�ѯ

			MySQLResultSet logRecord;
			m_DBDriver.SQLQuery(strSql, logRecord);
			
		}
		catch (...)
		{

		}
	}
	m_DBDriver.Disconnect();
}
LRESULT CMFCApplication1Dlg::PollNextPlan(WPARAM wParam, LPARAM lParam)
{
	char *p = (char*)lParam;
	UpdatePlanStatus(p,PLAN_STATUS_DONE);
	refreshData();
	std::list<PLANINFO>::iterator itList = m_planList.begin();
	for (; itList != m_planList.end(); itList++)
	{
		
		auto it = m_planList.begin();
		m_pollFun.SetPollPlan(*it);
		
		m_pollFun.StartPoll();
		break;
		
	}
	return 0;
}
void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	//m_player1.DoSnapPicture("f:\\test.bmp", 0);
	std::string planId = "2";
	::PostMessage(m_hOwner, WM_POLLINMIDITE, 0, (LPARAM)planId.c_str());
}
BEGIN_EVENTSINK_MAP(CMFCApplication1Dlg, CDialogEx)
	
	ON_EVENT(CMFCApplication1Dlg, IDC_PLAYERCTRL1, 9, CMFCApplication1Dlg::OnStreamInfoPlayerctrl1, VTS_BSTR)
	ON_EVENT(CMFCApplication1Dlg, IDC_PLAYERCTRL1, 6, CMFCApplication1Dlg::OnInviteFailedPlayerctrl1, VTS_I4)
	ON_EVENT(CMFCApplication1Dlg, IDC_WORKSPACECTRL1, 1, CMFCApplication1Dlg::OnInitSuccessedWorkspacectrl1, VTS_NONE)
	ON_EVENT(CMFCApplication1Dlg, IDC_WORKSPACECTRL1, 5, CMFCApplication1Dlg::OnGetDeviceListSuccessedWorkspacectrl1, VTS_BSTR)
	ON_EVENT(CMFCApplication1Dlg, IDC_WORKSPACECTRL1, 4, CMFCApplication1Dlg::OnGetDeviceListFailedWorkspacectrl1, VTS_I4)
	ON_EVENT(CMFCApplication1Dlg, IDC_WORKSPACECTRL1, 25, CMFCApplication1Dlg::OnGetDeviceListSuccessedExtWorkspacectrl1, VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CMFCApplication1Dlg, IDC_PLAYERCTRL1, 4, CMFCApplication1Dlg::OnStateChangedPlayerctrl1, VTS_I4)
	
	ON_EVENT(CMFCApplication1Dlg, IDC_PLAYERCTRL1, 8, CMFCApplication1Dlg::OnStreamCallBackPlayerctrl1, VTS_I4 VTS_PUI1 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


//void CMFCApplication1Dlg::OnStreamCallBackPlayerctrl1(long nDataType, unsigned char* pData, long nLength, long UserData)
//{
//	// TODO: �ڴ˴������Ϣ����������
//	char strtemp[1000] = {0};
//	sprintf_s(strtemp,"nDataType = %d ,nLenth = %d\r\n",nDataType,nLength);
//	OutputDebugString(strtemp);
//}


void CMFCApplication1Dlg::OnStreamInfoPlayerctrl1(LPCTSTR bstrXml)
{
	// TODO: �ڴ˴������Ϣ����������
	printf("4444");
	
	OutputDebugString("3341234234\n");
}

void CMFCApplication1Dlg::OnInviteFailedPlayerctrl1(long lType)
{
	// TODO: �ڴ˴������Ϣ����������
}


void CMFCApplication1Dlg::OnInitSuccessedWorkspacectrl1()
{
	// TODO: �ڴ˴������Ϣ����������
	//m_workspace.GetDeviceListExt(2, "32000000002160000001");
	
}


void CMFCApplication1Dlg::OnGetDeviceListSuccessedWorkspacectrl1(LPCTSTR bstrXml)
{
	// TODO: �ڴ˴������Ϣ����������
}


void CMFCApplication1Dlg::OnGetDeviceListFailedWorkspacectrl1(long lCode)
{
	// TODO: �ڴ˴������Ϣ����������
}


void CMFCApplication1Dlg::OnGetDeviceListSuccessedExtWorkspacectrl1(long Type, LPCTSTR bstrGroupId, LPCTSTR bstrXml)
{
	// TODO: �ڴ˴������Ϣ����������
	/*CString strmode = "<?xml version=\"1.0\"?> \
		<InviteConfig> \
		<TransParam TransMode=\"TCP-C\" StreamCBMode=\"\" /> \
		<VideoParam Codec=\"2\" Resolution=\"4\" Fps=\"25\" BRMode=\"1\" Kbps=\"2000\" Enbale=\"1\" />\
		</InviteConfig> ";


	m_player1.Invite("32000000001310000016", "", strmode);*/
}


void CMFCApplication1Dlg::OnStateChangedPlayerctrl1(long lType)
{
	// TODO: �ڴ˴������Ϣ����������
	if (lType == 0)
	{
		
	}
}




void CMFCApplication1Dlg::OnStreamCallBackPlayerctrl1(long nDataType, unsigned char* pData, long nLength, long UserData, long nWidth, long nHeight, long nFrameRate)
{
	// TODO: �ڴ˴������Ϣ����������

}
void CMFCApplication1Dlg::refreshData()
{
	//xml
	tinyxml2::XMLDocument doc;
	doc.LoadFile("c:\\setting.xml");
	const char* Address = doc.FirstChildElement("mysql")->FirstChildElement("Address")->GetText();
	const char* Port = doc.FirstChildElement("mysql")->FirstChildElement("Port")->GetText();
	const char* user = doc.FirstChildElement("mysql")->FirstChildElement("user")->GetText();
	const char* password = doc.FirstChildElement("mysql")->FirstChildElement("password")->GetText();

	const char* localip = doc.FirstChildElement("local")->FirstChildElement("ipaddress")->GetText();
	const char* localnat = doc.FirstChildElement("local")->FirstChildElement("nataddress")->GetText();
	//mysql
	MySQLDB m_DBDriver;
	//���ݿ�����
	if (!m_DBDriver.Connect(_T(Address), 3306, _T("zhyw"), _T(user), _T(password)))
	{
		m_DBDriver.Disconnect();
		return ;
	}
	if (!m_DBDriver.CheckDB())
	{
		return ;
	}
	else
	{
		try
		{

			//����SQL���
			std::string setchar = "set charset utf8;";
			//ִ�в�ѯ
			m_DBDriver.SQLExecute(setchar);

			//����SQL���
			std::string strSql = "SELECT *  FROM vqdplan  left join monvqd on vqdplan.ID=monvqd.VQD_ID left join collector on vqdplan.COLLECTOR_ID=collector.ID where DIA_TIME=1  AND IP_ADDRESS='" + std::string(localip) + "' or IP_ADDRESS='" + std::string(localnat) + "'";
			//ִ�в�ѯ

			MySQLResultSet logRecord;
			m_DBDriver.SQLQuery(strSql, logRecord);
			int nRowCount = (int)logRecord.size();
			if (!nRowCount)return ;
			m_planList.clear();
			for (int i = 0; i < nRowCount; i++)
			{
				PLANINFO plan;
				plan.InitData();
				if (logRecord[i]["COL_INTERVAL"] == "") {
					plan.wInterval = 60;
				}
				else
					plan.wInterval = atol(logRecord[i]["COL_INTERVAL"].c_str());
				plan.strPlanName = logRecord[i]["COL_PLAN_NAME"];
				tagPosInfo tag;
				tag.strPosID = logRecord[i]["MON_ID"];
				plan.lstDevice.push_back(tag);
				plan.wVidCount = PLAN_COUNT;
				if (logRecord[i]["MONDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["MONDAY"]);
				}
				if (logRecord[i]["TUESDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["TUESDAY"]);
				}
				if (logRecord[i]["WEDNESDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["WEDNESDAY"]);
				}
				if (logRecord[i]["THURSDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["THURSDAY"]);
				}
				if (logRecord[i]["FRIDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["FRIDAY"]);
				}
				if (logRecord[i]["SATURDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["SATURDAY"]);
				}
				if (logRecord[i]["SUNDAY"] != "") {
					plan.strTimeList.push_back(logRecord[i]["SUNDAY"]);
				}
				m_planList.push_back(plan);

			}
			
		}
		catch (...)
		{

		}
	}
	m_DBDriver.Disconnect();
}