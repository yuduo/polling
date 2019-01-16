
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "playerctrl1.h"
#include "workspacectrl1.h"


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

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CPlayerctrl1 m_player;
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
};
