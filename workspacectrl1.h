#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CWorkspacectrl1 包装类

class CWorkspacectrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWorkspacectrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x779C82F4, 0x182F, 0x4D0C, { 0x84, 0x7C, 0x11, 0xC0, 0x1B, 0xF1, 0xAC, 0x74 } };
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
enum
{
    eRcOk = 0,
    eRcHasInit = 10,
    eRcHasnotInit = 11,
    eRcInvalidParam = 12,
    eRcInvalidLink = 13,
    eRcInvalidCmd = 14,
    eRcCmsConnectFailed = 20,
    eRcCmsInvalidResponse = 21,
    eRcMsgBuildRequestFailed = 30,
    eReMsgBuildResponseFailed = 31,
    eRcMsgParseRequestFailed = 32,
    eReMsgParseResponseFailed = 33,
    eRcMsgResponseError = 34,
    eRcSipInitFailed = 40,
    eRcSipRegFailed = 41,
    eRcSipCreateRequestFailed = 42,
    eRcSipSendRequestFialed = 43,
    eRcSipInvalidSession = 44,
    eRcSipRespForbidden = 50,
    eRcSipRespNotFound = 51,
    eRcSipRespRequestTimeout = 52,
    eRcSipRespBusy = 53,
    eRcSipRespServer = 54,
    eRcSipRespNull = 55,
    eRcRpCreatePlayFaild = 60,
    eRcRpInitPlayFiald = 61,
    eRcRpCreateRtpFaild = 62,
    eRcRpStartPlayFaild = 63,
    eRcRpStartRtpFaild = 64,
    eRcRpOpenFileFaild = 65,
    eRcRpInvalidFile = 66
}ERetvalCode;


// 操作
public:

// IWorkspaceCtrl

// Functions
//

	long Init(LPCTSTR bstrUserId, LPCTSTR bstrUserName, LPCTSTR bstrPassWord, LPCTSTR bstrServerId, LPCTSTR bstrServerIp, long lServerPort)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrUserId, bstrUserName, bstrPassWord, bstrServerId, bstrServerIp, lServerPort);
		return result;
	}
	void Uninit()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long GetDeviceList()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long DeviceControl(LPCTSTR bstrDeviceId, LPCTSTR bstrChannelId, long lType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceId, bstrChannelId, lType);
		return result;
	}
	long RecordQuery(LPCTSTR bstrDeviceId, LPCTSTR bstrStartTime, LPCTSTR bstrEndTime, LPCTSTR bstrFilePath, LPCTSTR bstrAddress, long lSecrecy, long lType, LPCTSTR bstrRecorderId)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceId, bstrStartTime, bstrEndTime, bstrFilePath, bstrAddress, lSecrecy, lType, bstrRecorderId);
		return result;
	}
	long GetDeviceInfo(LPCTSTR bstrDeviceId)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceId);
		return result;
	}
	long GetDeviceStatus(LPCTSTR bstrDeviceId)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceId);
		return result;
	}
	long DecoderControl(LPCTSTR bstrDecoderId, LPCTSTR bstrDeviceId, long lStart, long PlayMode, LPCTSTR strStartTime, LPCTSTR strEndTime)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDecoderId, bstrDeviceId, lStart, PlayMode, strStartTime, strEndTime);
		return result;
	}
	long GetDecoderInfo(LPCTSTR bstrDecoderId)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDecoderId);
		return result;
	}
	long LocalPlanAdd(LPCTSTR Name, long Plan, long TVWallPlanID, long ViewMode, long timer, LPCTSTR UserID, long Type, long Interval, LPCTSTR RunMode, LPCTSTR BeginTime, LPCTSTR EndTime, LPCTSTR UpdateTime, long Period, LPCTSTR PeriodArge, LPCTSTR xml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Name, Plan, TVWallPlanID, ViewMode, timer, UserID, Type, Interval, RunMode, BeginTime, EndTime, UpdateTime, Period, PeriodArge, xml);
		return result;
	}
	long UpdateLocalPlan(long PlanId, long Plan, long TVWallPlanID, LPCTSTR Name, long ViewMode, long timer, LPCTSTR UserID, long Type, long Interval, LPCTSTR RunMode, LPCTSTR BeginTime, LPCTSTR EndTime, long Period, LPCTSTR PeriodArge, LPCTSTR xml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanId, Plan, TVWallPlanID, Name, ViewMode, timer, UserID, Type, Interval, RunMode, BeginTime, EndTime, Period, PeriodArge, xml);
		return result;
	}
	long DeleteLocalPlan(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long DeletePlanResource(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long QueryLocalPlanList(LPCTSTR UserID, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserID, sXml);
		return result;
	}
	long QueryLocalPlan(LPCTSTR PlanName, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanName, sXml);
		return result;
	}
	long QueryPlanResourceList(long PlanId, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanId, sXml);
		return result;
	}
	long ScreenPlanAdd(LPCTSTR Name, long ViewMode, long timer, LPCTSTR UserID, long Interval, LPCTSTR MergeContent, LPCTSTR UpdateTime, LPCTSTR Monxml, LPCTSTR Camxml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Name, ViewMode, timer, UserID, Interval, MergeContent, UpdateTime, Monxml, Camxml);
		return result;
	}
	long EditScreenPlan(LPCTSTR Name, long timer, long Interval, long PlanId)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Name, timer, Interval, PlanId);
		return result;
	}
	long DelScreenPlan(long PlanId)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanId);
		return result;
	}
	long DelScreenPlanMonitor(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long DelScreenPlanCamera(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long QueryScreenPlanList(LPCTSTR UserID, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserID, sXml);
		return result;
	}
	long QueryScreenPlan(LPCTSTR PlanName, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanName, sXml);
		return result;
	}
	long QueryPlanMonitorList(long PlanId, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanId, sXml);
		return result;
	}
	long QueryPlanCameraList(long PlanId, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanId, sXml);
		return result;
	}
	long TVWallPlanAdd(LPCTSTR Name, long ViewMode, LPCTSTR UserID, LPCTSTR MergeContent, LPCTSTR UpdateTime, LPCTSTR Monxml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Name, ViewMode, UserID, MergeContent, UpdateTime, Monxml);
		return result;
	}
	long EditTVWallPlan(LPCTSTR Name, long ID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Name, ID);
		return result;
	}
	long DelTVWallPlan(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long DelTVWallPlanMonitor(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long QueryTVWallPlanList(LPCTSTR UserID, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserID, sXml);
		return result;
	}
	long QueryTVWallPlan(LPCTSTR PlanName, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanName, sXml);
		return result;
	}
	long QueryTVWallPlanMonitorList(long PlanId, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanId, sXml);
		return result;
	}
	long VideoSwitch(LPCTSTR CamID, LPCTSTR MonID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, parms, CamID, MonID);
		return result;
	}
	long AddCruise(LPCTSTR CruiseName, LPCTSTR UserID, LPCTSTR UpdateTime, LPCTSTR PresetXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_I4, (void*)&result, parms, CruiseName, UserID, UpdateTime, PresetXml);
		return result;
	}
	long EditCruise(LPCTSTR CruiseName, long CruiseID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, parms, CruiseName, CruiseID);
		return result;
	}
	long DelCruise(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long DelPreset(long PresetID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PresetID);
		return result;
	}
	long QueryCruiseList(LPCTSTR UserID, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserID, sXml);
		return result;
	}
	long QueryCruise(LPCTSTR CruiseName, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, parms, CruiseName, sXml);
		return result;
	}
	long QueryPresetList(long CruiseID, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, parms, CruiseID, sXml);
		return result;
	}
	long AddLabel(LPCTSTR LabelName, LPCTSTR UserID, LPCTSTR CamID, LPCTSTR PlayBackTime, LPCTSTR UpdateTime)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LabelName, UserID, CamID, PlayBackTime, UpdateTime);
		return result;
	}
	long EditLabel(LPCTSTR LabelName, LPCTSTR PlayBackTime, long ID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LabelName, PlayBackTime, ID);
		return result;
	}
	long DelLabel(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long QueryLabelList(LPCTSTR LabelName, LPCTSTR UserID, LPCTSTR CamID, LPCTSTR StartTime, LPCTSTR EndTime, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LabelName, UserID, CamID, StartTime, EndTime, BeginNum, EndNum, iResult, sXml);
		return result;
	}
	long QueryLabel(LPCTSTR LabelName, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LabelName, BeginNum, EndNum, iResult, sXml);
		return result;
	}
	long UpdateMap(long MapID, LPCTSTR MapName, long ParentMapID, LPCTSTR MapImage, long LIPX, long LIPY, long Width, long Height, LPCTSTR CreateTime, LPCTSTR Lastupdatetime, LPCTSTR MapType, long IsAdd)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, MapID, MapName, ParentMapID, MapImage, LIPX, LIPY, Width, Height, CreateTime, Lastupdatetime, MapType, IsAdd);
		return result;
	}
	long DelMap(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long QueryMapList(BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sXml);
		return result;
	}
	long UpdateMapElement(long MapElementID, LPCTSTR MapElementName, long ParentGroupID, LPCTSTR ParentGroupName, long ParentMapID, long LIPX, long LIPY, long RIPX, long RIPY, long MapElementType, long MapElementTypeAdd, long DeviceGlbID, long CamGlbID, LPCTSTR Factory, long STATE, long LOCATIONINDEX, long IsAdd)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, parms, MapElementID, MapElementName, ParentGroupID, ParentGroupName, ParentMapID, LIPX, LIPY, RIPX, RIPY, MapElementType, MapElementTypeAdd, DeviceGlbID, CamGlbID, Factory, STATE, LOCATIONINDEX, IsAdd);
		return result;
	}
	long DelMapElement(long MapElementID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, MapElementID);
		return result;
	}
	long SelectMapElementList(BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sXml);
		return result;
	}
	long GetUserPower(LPCTSTR UserName, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserName, sXml);
		return result;
	}
	long QueryMapImage(long ID, BSTR * sImage)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, sImage);
		return result;
	}
	long InitNew(LPCTSTR bstrUserName, LPCTSTR bstrPassWord, LPCTSTR bstrServerIp, long lServerPort)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrUserName, bstrPassWord, bstrServerIp, lServerPort);
		return result;
	}
	long GetAlarmLog(LPCTSTR DeviceID, long Method, LPCTSTR BeginTime, LPCTSTR EndTime, long Priority, LPCTSTR Description, long ID, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_I4, (void*)&result, parms, DeviceID, Method, BeginTime, EndTime, Priority, Description, ID, BeginNum, EndNum, iResult, sXml);
		return result;
	}
	long UpdateChanExtTbl(LPCTSTR ChanPubID, long X, long Y, long label)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ChanPubID, X, Y, label);
		return result;
	}
	long QueryLabelByTime(LPCTSTR StartTime, LPCTSTR EndTime, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_I4, (void*)&result, parms, StartTime, EndTime, sXml);
		return result;
	}
	long PtzControl(LPCTSTR strDeviceId, long lActionType, long lActionInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceId, lActionType, lActionInfo);
		return result;
	}
	long GetAlarmLogAll(LPCTSTR DeviceID, long Method, LPCTSTR BeginTime, LPCTSTR EndTime, long ID, long Priority, LPCTSTR Description, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, DeviceID, Method, BeginTime, EndTime, ID, Priority, Description, iResult, sXml);
		return result;
	}
	long GetUserLog(LPCTSTR UserName, LPCTSTR BeginTime, LPCTSTR EndTime, long nType, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserName, BeginTime, EndTime, nType, BeginNum, EndNum, iResult, sXml);
		return result;
	}
	long DeviceLockControl(LPCTSTR strDeviceId, long lLockType, long lLockSecond)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceId, lLockType, lLockSecond);
		return result;
	}
	long GetDevicePara(LPCTSTR bstrDeviceId, long lType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceId, lType);
		return result;
	}
	long UpdateKBSnapPicture(LPCTSTR UserName, LPCTSTR DateTimes, long ImageID, LPCTSTR CameraName, long PictureNumber, LPCTSTR PictureName, LPCTSTR VideoName, LPCTSTR FTPPath, LPCTSTR InfoStatus)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserName, DateTimes, ImageID, CameraName, PictureNumber, PictureName, VideoName, FTPPath, InfoStatus);
		return result;
	}
	long GetKBSnapPicture(LPCTSTR UserName, LPCTSTR BeginTime, LPCTSTR EndTime, LPCTSTR CameraName, LPCTSTR PictureName, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserName, BeginTime, EndTime, CameraName, PictureName, BeginNum, EndNum, iResult, sXml);
		return result;
	}
	long AudioBroadCast(LPCTSTR ScrDevID, LPCTSTR pDstDevID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ScrDevID, pDstDevID);
		return result;
	}
	long DragZomm(LPCTSTR ChanPubID, long IsZoomIn, long nLenth, long nWidth, long nMidPointX, long nMidPointY, long LengthX, long LengthY)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ChanPubID, IsZoomIn, nLenth, nWidth, nMidPointX, nMidPointY, LengthX, LengthY);
		return result;
	}
	long DeviceConfigQuery(LPCTSTR bstrDeviceId, long lConfigType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceId, lConfigType);
		return result;
	}
	long DeviceConfigSet(LPCTSTR bstrDeviceId, LPCTSTR sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x44, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceId, sXml);
		return result;
	}
	long QueryUserList(long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x45, DISPATCH_METHOD, VT_I4, (void*)&result, parms, iResult, sXml);
		return result;
	}
	long AddGuardPos(LPCTSTR ChanPubID, long GuardPos)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x46, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ChanPubID, GuardPos);
		return result;
	}
	long GetGuardPos(LPCTSTR ChanPubID, long * GuardPos)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_PI4 ;
		InvokeHelper(0x47, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ChanPubID, GuardPos);
		return result;
	}
	long VideoSplitterControl(LPCTSTR bstrDeviceId, long SplitScreenType, long nChannel)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x48, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceId, SplitScreenType, nChannel);
		return result;
	}
	long VideoSplitterQuery(LPCTSTR bstrDeviceId)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x49, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceId);
		return result;
	}
	long GetPlanSequence(LPCTSTR UserID, LPCTSTR Name, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserID, Name, sXml);
		return result;
	}
	long GetPlanSeqResource(long PlanSequenceID, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x4b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PlanSequenceID, BeginNum, EndNum, iResult, sXml);
		return result;
	}
	long GetPollPlan(LPCTSTR UserID, LPCTSTR Name, long PollMode, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x4c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserID, Name, PollMode, sXml);
		return result;
	}
	long GetPollAutoPlan(LPCTSTR UserID, LPCTSTR Name, long PlanMode, LPCTSTR BeginTime, LPCTSTR EndTime, long PlanState, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x4d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserID, Name, PlanMode, BeginTime, EndTime, PlanState, sXml);
		return result;
	}
	long UpdatePlanSequence(long ID, LPCTSTR Name, long SeqInter, LPCTSTR UserID, LPCTSTR MonitorIndex, long IsAdd, long * iCurID)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_PI4 ;
		InvokeHelper(0x4e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, Name, SeqInter, UserID, MonitorIndex, IsAdd, iCurID);
		return result;
	}
	long DelPlanSequence(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long UpdatePlanSeqResource(long ID, long PlanSequenceID, long PresetPos, LPCTSTR CamID, LPCTSTR MonitorID, long Index, long IsAdd)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x50, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, PlanSequenceID, PresetPos, CamID, MonitorID, Index, IsAdd);
		return result;
	}
	long DelPlanSeqResource(long ID, long SingleDel)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x51, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, SingleDel);
		return result;
	}
	long UpdatePollPlan(long ID, LPCTSTR Name, LPCTSTR UserID, long ScreenNo, long Runtimes, long Interval, LPCTSTR UpdateTime, long PollMode, long IsAdd, long * iCurID)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_PI4 ;
		InvokeHelper(0x52, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, Name, UserID, ScreenNo, Runtimes, Interval, UpdateTime, PollMode, IsAdd, iCurID);
		return result;
	}
	long DelPollPlan(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x53, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long UpdatePlanSequenceUnion(long ID, long PlanSequenceID, long PollPlanID, long Index, long IsAdd)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x54, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, PlanSequenceID, PollPlanID, Index, IsAdd);
		return result;
	}
	long DelPlanSequenceUnion(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x55, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long UpdatePlanMonitor(long ID, LPCTSTR MonID, long PollAutoPlanID, long Index, long IsAdd)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x56, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, MonID, PollAutoPlanID, Index, IsAdd);
		return result;
	}
	long DelPlanMonitor(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x57, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long UpdatePlanUserUnion(long ID, LPCTSTR UserID, long PollPlanID, long IsAdd)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x58, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, UserID, PollPlanID, IsAdd);
		return result;
	}
	long DelPlanUserUnion(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x59, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long UpdatePollAutoPlan(long ID, LPCTSTR Name, LPCTSTR UserID, long RunMode, LPCTSTR WeekMode, LPCTSTR BeginTime, LPCTSTR EndTime, LPCTSTR UpdateTime, long PollPlanID, long PlanState, long PlanMode, long IsAdd, long * iCurID)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4 ;
		InvokeHelper(0x5a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, Name, UserID, RunMode, WeekMode, BeginTime, EndTime, UpdateTime, PollPlanID, PlanState, PlanMode, IsAdd, iCurID);
		return result;
	}
	long DelPollAutoPlan(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long StartTalking(LPCTSTR bstrDstDevID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDstDevID);
		return result;
	}
	long StopTalking(LPCTSTR bstrDstDevID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDstDevID);
		return result;
	}
	long DeviceLockQuery(LPCTSTR pDeviceId, long LockType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x5e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDeviceId, LockType);
		return result;
	}
	long GetDeviceListExt(long nType, LPCTSTR GroupId)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x5f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nType, GroupId);
		return result;
	}
	long ScreenControl(LPCTSTR TVWallPlan)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x60, DISPATCH_METHOD, VT_I4, (void*)&result, parms, TVWallPlan);
		return result;
	}
	long UpdateUsrAndPwd(LPCTSTR OldName, LPCTSTR OldPwd, LPCTSTR NewName, LPCTSTR NewPwd)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x61, DISPATCH_METHOD, VT_I4, (void*)&result, parms, OldName, OldPwd, NewName, NewPwd);
		return result;
	}
	long UpdateRealTime()
	{
		long result;
		InvokeHelper(0x62, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long AddUserOperLog(long eType, LPCTSTR strOperation)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x63, DISPATCH_METHOD, VT_I4, (void*)&result, parms, eType, strOperation);
		return result;
	}
	long GetProjectInformation(long ProjectID, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x64, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ProjectID, BeginNum, EndNum, iResult, sXml);
		return result;
	}
	long DeviceControlExt(LPCTSTR pDeviceId, LPCTSTR pChannelId, long nType, long nType2, long nType3, long nType4)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDeviceId, pChannelId, nType, nType2, nType3, nType4);
		return result;
	}
	long QueryPreset(LPCTSTR pDeviceId)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDeviceId);
		return result;
	}
	long QueryDeviceMobilePosition(LPCTSTR pDeviceId, long Interval)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDeviceId, Interval);
		return result;
	}
	long QueryAlarm(LPCTSTR pDeviceId, LPCTSTR pStartTime, LPCTSTR pEndTime)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDeviceId, pStartTime, pEndTime);
		return result;
	}
	long GetZDITables(long nType, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nType, sXml);
		return result;
	}
	long GetUserLogExt(LPCTSTR UserName, LPCTSTR BeginTime, LPCTSTR EndTime, long nType, LPCTSTR CamID, LPCTSTR MonID, long Result, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, UserName, BeginTime, EndTime, nType, CamID, MonID, Result, BeginNum, EndNum, iResult, sXml);
		return result;
	}
	long AddUserOperLogExt(long eType, LPCTSTR strOperation, LPCTSTR CamID, LPCTSTR MonID, long Result)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, eType, strOperation, CamID, MonID, Result);
		return result;
	}
	long GetSubChannel(LPCTSTR DeviceID, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, DeviceID, BeginNum, EndNum, iResult, sXml);
		return result;
	}
	long GetSystemInfo(BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, sXml);
		return result;
	}
	long UpdateFavoriteGroup(long IsAdd, long GroupId, long ParentID, LPCTSTR GroupName, LPCTSTR CreateUser, long IsPublic)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, IsAdd, GroupId, ParentID, GroupName, CreateUser, IsPublic);
		return result;
	}
	long DelFavoriteGroup(long GroupId)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, GroupId);
		return result;
	}
	long UpdateFavoriteDevice(long IsAdd, long ID, long ParentGroupID, LPCTSTR DeviceID)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x70, DISPATCH_METHOD, VT_I4, (void*)&result, parms, IsAdd, ID, ParentGroupID, DeviceID);
		return result;
	}
	long DelFavoriteDevice(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x71, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	long GetFavoriteInfo(long GroupId, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x72, DISPATCH_METHOD, VT_I4, (void*)&result, parms, GroupId, sXml);
		return result;
	}
	long GetGpsTrackInfo(LPCTSTR DeviceID, LPCTSTR BeginTime, LPCTSTR EndTime, long BeginNum, long EndNum, long * iResult, BSTR * sXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_I4, (void*)&result, parms, DeviceID, BeginTime, EndTime, BeginNum, EndNum, iResult, sXml);
		return result;
	}

// Properties
//



};
