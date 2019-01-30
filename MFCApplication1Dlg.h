
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "playerctrl1.h"
#include "workspacectrl1.h"
#include "iNetworkInterface.h"
#include "resource.h"
#include "PollDataCfg.h"
#include "PollFunction.h"
// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	
// 实现
protected:
	HICON m_hIcon;

	LRESULT OnHandleMessage(WPARAM wParam, LPARAM lParam);

	static unsigned int __stdcall ThreadPollImmediate(void * pParam);

	LRESULT PollImmidate(WPARAM wParam, LPARAM lParam);

	void AnalysisOne(std::string strPosID, int nscount, IMAGECOMPARE compare);

	BOOL SaveSnapImage(int index, std::string strFilePath);

	LRESULT PollMessageHandle(WPARAM wParam, LPARAM lParam);

	void ImageResultToDB(std::string strFilePath, int count, IMAGECOMPARE compare);

	void Stop(int index);

	BOOL OpenVideo(std::string strPosID, int index);

	PLANINFO getPlanInfo(std::string strID);

	LRESULT  ShowSnapPoll(WPARAM wParam, LPARAM lParam);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void UpdatePlanStatus(std::string strID, int type);
	LRESULT PollNextPlan(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CPlayerctrl1 m_player1;
	CPlayerctrl1 m_player2;
	CPlayerctrl1 m_player3;
	CPlayerctrl1 m_player4;
	CPlayerctrl1 m_player5;
	CPlayerctrl1 m_player6;
	CWorkspacectrl1 m_workspace;
	DECLARE_EVENTSINK_MAP()
	
	void OnStreamInfoPlayerctrl1(LPCTSTR bstrXml);
	VOID OnInitSuccessed();
	VOID OnInitFailed(LONG lCode);
	void OnInviteFailedPlayerctrl1(long lType);
	void OnInitSuccessedWorkspacectrl1();
	void OnGetDeviceListSuccessedWorkspacectrl1(LPCTSTR bstrXml);
	void OnGetDeviceListFailedWorkspacectrl1(long lCode);
	void OnGetDeviceListSuccessedExtWorkspacectrl1(long Type, LPCTSTR bstrGroupId, LPCTSTR bstrXml);
	void OnStateChangedPlayerctrl1(long lType);
	void OnStreamCallBackPlayerctrl1(long nDataType, unsigned char* pData, long nLength, long UserData, long nWidth, long nHeight, long nFrameRate);

	void refreshData();

	INetAcceptor *p_TcpAcceptor;
	CPollFunction m_pollFun;
	CPollFunction m_pollFun1;
	std::string m_planid;
	HANDLE      m_hThread;
	std::list< PLANINFO> m_planList;
public:
	static int m_immediteSession;
	static HWND					m_hOwner;
	
};
