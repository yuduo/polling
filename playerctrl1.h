#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CPlayerctrl1 包装类

class CPlayerctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CPlayerctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x34CFA83A, 0x6845, 0x4EDE, { 0x98, 0xEC, 0x40, 0xB, 0x4A, 0x4A, 0x4F, 0x85 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:


// 操作
public:

// IPlayerCtrl

// Functions
//

	long ConnectToWorkspace(LPDISPATCH pWorkspace)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pWorkspace);
		return result;
	}
	void DisConnect()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Stop()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long Invite(LPCTSTR btrDeviceId, LPCTSTR bstrManufacturer, LPCTSTR bstrModel)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, btrDeviceId, bstrManufacturer, bstrModel);
		return result;
	}
	long PtzControl(long lActionType, long lActionInfo)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lActionType, lActionInfo);
		return result;
	}
	long Vod(LPCTSTR btrDeviceId, LPCTSTR bstrBeginTime, LPCTSTR bstrEndTime, LPCTSTR bstrManufacturer, LPCTSTR bstrModel, long boolSaveFile, LPCTSTR bstrSavePath, LPCTSTR bstrAddress)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, btrDeviceId, bstrBeginTime, bstrEndTime, bstrManufacturer, bstrModel, boolSaveFile, bstrSavePath, bstrAddress);
		return result;
	}
	long Pause()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long Play(long lStartTime, double dSpeed)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lStartTime, dSpeed);
		return result;
	}
	long OpenFile(LPCTSTR bstrPath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrPath);
		return result;
	}
	void StartRecord(LPCTSTR strPath, long nDuration)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strPath, nDuration);
	}
	void DoSnapPicture(LPCTSTR sPath, long nType)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sPath, nType);
	}
	void StopRecord()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DigitalScale(long RectLeft, long RectTop, long RectRight, long RectBottom, long Enable)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, RectLeft, RectTop, RectRight, RectBottom, Enable);
	}
	void SetImagePara(long Brightness, long Contrast, long Enable, long BufferLevel)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Brightness, Contrast, Enable, BufferLevel);
	}
	void SaveImage(long x, long y, long w, long h, LPCTSTR filepath)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y, w, h, filepath);
	}
	long PlayLocalVideo(LPCTSTR filepath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms, filepath);
		return result;
	}
	long ControlLocalVideo(long type, double para)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, type, para);
		return result;
	}
	long VodVideo(LPCTSTR btrDeviceId, LPCTSTR bstrBeginTime, LPCTSTR bstrEndTime, LPCTSTR bstrManufacturer, LPCTSTR bstrModel, LPCTSTR bstrAddress)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms, btrDeviceId, bstrBeginTime, bstrEndTime, bstrManufacturer, bstrModel, bstrAddress);
		return result;
	}
	long VodDownload(LPCTSTR btrDeviceId, LPCTSTR bstrBeginTime, LPCTSTR bstrEndTime, LPCTSTR bstrManufacturer, LPCTSTR bstrModel, LPCTSTR bstrSavePath, LPCTSTR bstrAddress)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, btrDeviceId, bstrBeginTime, bstrEndTime, bstrManufacturer, bstrModel, bstrSavePath, bstrAddress);
		return result;
	}
	long DrawBoxRect(long x, long y, long Width, long Height, long Red, long Green, long Blue)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, x, y, Width, Height, Red, Green, Blue);
		return result;
	}
	long OpenAudio(long bMute)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bMute);
		return result;
	}
	long VodSlice(LPCTSTR btrDeviceId, LPCTSTR bstrBeginTime, LPCTSTR bstrEndTime, LPCTSTR bstrManufacturer, LPCTSTR bstrModel, LPCTSTR bstrSavePath, long nInterval, LPCTSTR bstrAddress)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, btrDeviceId, bstrBeginTime, bstrEndTime, bstrManufacturer, bstrModel, bstrSavePath, nInterval, bstrAddress);
		return result;
	}
	long PlayExt(long lPlayType, long lStartTime, double dSpeed)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lPlayType, lStartTime, dSpeed);
		return result;
	}
	void SetStreamCBUserData(long UserData)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, UserData);
	}
	long Rotate(long nMode)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nMode);
		return result;
	}
	long InviteExt(LPCTSTR pUrl, LPCTSTR pDevIP, long nDevPort, LPCTSTR pDevUsr, LPCTSTR pDevPwd, long lRealStreamMode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pUrl, pDevIP, nDevPort, pDevUsr, pDevPwd, lRealStreamMode);
		return result;
	}

// Properties
//



};
