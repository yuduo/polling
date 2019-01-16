
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once
#include "playerctrl1.h"
#include "workspacectrl1.h"


// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
