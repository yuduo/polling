
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "tinyxml2.h"
#include "MySQLDB.h"
#include "Socket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAYERCTRL1, m_player);
	DDX_Control(pDX, IDC_WORKSPACECTRL1, m_workspace);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()

unsigned __stdcall Answer(void* a) {
	Socket* s = (Socket*)a;

	//while (1) {
		std::string r = s->ReceiveLine();
		//if (r.empty()) break;
		s->SendLine(r);
	//}

	delete s;

	return 0;
}

// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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
	//数据库驱动
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

			//创建SQL语句
			std::string setchar = "set charset gbk;";
			//执行查询
			m_DBDriver.SQLExecute(setchar);

			//创建SQL语句
			std::string strSql = "SELECT *  FROM vqdplan";
			//执行查询

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

	//socket
	/*SocketServer in(2000, 5);

	while (1) {
		Socket* s = in.Accept();

		unsigned ret;
		_beginthreadex(0, 0, Answer, (void*)s, 0, &ret);
	}*/
	NetworkInit();
	iNetworkInterface *p_iNetInface = new iNetworkInterface();
	//p_TcpAcceptor = CreateTcpAcceptor((INetAcceptorSink*)p_iNetInface);	
	p_TcpAcceptor = CreateRawTcpAcceptor(p_iNetInface);
	p_TcpAcceptor->StartListen(2000);//监听端口/hostIP(默认全部监听)


	m_workspace.InitNew("admin","123456","122.112.203.74",8083);

	m_player.ConnectToWorkspace(lpdisp);//
	 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	m_player.DoSnapPicture("f:\\test.bmp", 0);
	
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
//	// TODO: 在此处添加消息处理程序代码
//	char strtemp[1000] = {0};
//	sprintf_s(strtemp,"nDataType = %d ,nLenth = %d\r\n",nDataType,nLength);
//	OutputDebugString(strtemp);
//}


void CMFCApplication1Dlg::OnStreamInfoPlayerctrl1(LPCTSTR bstrXml)
{
	// TODO: 在此处添加消息处理程序代码
	printf("4444");
	OutputDebugString("3341234234\n");
}

void CMFCApplication1Dlg::OnInviteFailedPlayerctrl1(long lType)
{
	// TODO: 在此处添加消息处理程序代码
}


void CMFCApplication1Dlg::OnInitSuccessedWorkspacectrl1()
{
	// TODO: 在此处添加消息处理程序代码
	m_workspace.GetDeviceListExt(2, "32000000002160000001");
}


void CMFCApplication1Dlg::OnGetDeviceListSuccessedWorkspacectrl1(LPCTSTR bstrXml)
{
	// TODO: 在此处添加消息处理程序代码
}


void CMFCApplication1Dlg::OnGetDeviceListFailedWorkspacectrl1(long lCode)
{
	// TODO: 在此处添加消息处理程序代码
}


void CMFCApplication1Dlg::OnGetDeviceListSuccessedExtWorkspacectrl1(long Type, LPCTSTR bstrGroupId, LPCTSTR bstrXml)
{
	// TODO: 在此处添加消息处理程序代码
	CString strmode = "<?xml version=\"1.0\"?> \
		<InviteConfig> \
		<TransParam TransMode=\"TCP-C\" StreamCBMode=\"\" /> \
		<VideoParam Codec=\"2\" Resolution=\"4\" Fps=\"25\" BRMode=\"1\" Kbps=\"2000\" Enbale=\"1\" />\
		</InviteConfig> ";

	//m_player.Invite("32050912001310000042","","");YUV
	m_player.Invite("32000000001310000015", "", strmode);
}


void CMFCApplication1Dlg::OnStateChangedPlayerctrl1(long lType)
{
	// TODO: 在此处添加消息处理程序代码
}




void CMFCApplication1Dlg::OnStreamCallBackPlayerctrl1(long nDataType, unsigned char* pData, long nLength, long UserData, long nWidth, long nHeight, long nFrameRate)
{
	// TODO: 在此处添加消息处理程序代码
}
