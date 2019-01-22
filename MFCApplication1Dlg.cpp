
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

#pragma comment(lib,"VQSModule.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
HWND				CMFCApplication1Dlg::m_hOwner;
const HWND GetMainHwnd()
{
	return CMFCApplication1Dlg::m_hOwner;
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
	
END_MESSAGE_MAP()

LRESULT CMFCApplication1Dlg::PollImmidate(WPARAM wParam, LPARAM lParam)
{
	m_pollFun.StartImmediate();
	return 0;
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
	int nCount = LOWORD(lParam);

	int nind = nIndex - nCount;
	if (nind < 0)
	{
		nind = 0;
	}
	int nscount = 0;
	std::list<tagPosInfo>::iterator itDmList = m_tCurPlanInfo.lstDevice.begin();
	//û��ץ�ı�־����ץ��
	if (m_tCurPlanInfo.wSnapFlag != 1)
	{
		return 1;
	}

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
			sprintf((char*)strPat.c_str(), "%s\\%s\\", "f:", m_tCurPlanInfo.strPlanName.c_str());
			//��ͼ������Ӧ��Ŀ¼��
			SYSTEMTIME sm;
			GetLocalTime(&sm);
			std::string strFilePath;


			sprintf((char*)strFilePath.c_str(), _T("%s/%s_%d%02d%02d_%02d%02d%02d.jpg"), strPat.c_str(), itDmList->strPosID.c_str(),
				sm.wYear, sm.wMonth, sm.wDay,
				sm.wHour, sm.wMinute, sm.wSecond);
			SaveSnapImage(nscount, strFilePath);
			RESULT_VALUE lpResultOut;
			if(VQS_API_GetVQSResult(strFilePath.c_str(),&lpResultOut))
			{
				//�������ݿ�
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
LRESULT  CMFCApplication1Dlg::ShowSnapPoll(WPARAM wParam, LPARAM lParam)
{
	int nIndex = LOWORD(wParam);
	int nCount = LOWORD(lParam);

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
			std::string setchar = "set charset gbk;";
			//ִ�в�ѯ
			m_DBDriver.SQLExecute(setchar);

			//����SQL���
			std::string strSql = "SELECT *  FROM vqdplan";
			//ִ�в�ѯ

			MySQLResultSet logRecord;
			m_DBDriver.SQLQuery(strSql, logRecord);
			int nRowCount = (int)logRecord.size();
			if (!nRowCount)return 0;
			for (int i = 0; i < nRowCount; i++)
			{
				//lastName = logRecord[nRowCount - 1]["log_name"];

			}
		}
		catch (...)
		{

		}
	}

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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
	m_player1.DoSnapPicture("f:\\test.bmp", 0);
	
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
	m_workspace.GetDeviceListExt(2, "32000000002160000001");
	
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
	CString strmode = "<?xml version=\"1.0\"?> \
		<InviteConfig> \
		<TransParam TransMode=\"TCP-C\" StreamCBMode=\"\" /> \
		<VideoParam Codec=\"2\" Resolution=\"4\" Fps=\"25\" BRMode=\"1\" Kbps=\"2000\" Enbale=\"1\" />\
		</InviteConfig> ";


	m_player1.Invite("32000000001310000016", "", strmode);
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
