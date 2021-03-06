#pragma once
#include <list>
#include <vector>

#define DEFINE_XML_POLLPLAN_APPFIG	         _T("PlanConfig")

#define DEFINE_XML_POLLPLAN_VAL              _T("Values")
#define MAIN_POLL_VERSION	                 _T("2.2.3")

#define DEFINE_XML_POLLPLAN_VESION	         _T("Vesion")

#define DEFINE_XML_POLLPLAN_INFO	         _T("PlanInfo")

#define DEFINE_XML_POLLPLAN_NAME            _T("Name")
#define DEFINE_XML_POLLPLAN_TYPE            _T("PlanType")
#define DEFINE_XML_POLLPLAN_VIDNUM	        _T("VIDCount")
#define DEFINE_XML_POLLPLAN_INTVAL	        _T("Interval")
#define DEFINE_XML_POLLPLAN_SNAP	        _T("SnapShot")
#define DEFINE_XML_POLLPLAN_FORCESW	        _T("ForceSW")

#define DEFINE_XML_POLLPLAN_DATECFG	        _T("DateConfig")
#define DEFINE_XML_POLLPLAN_DATEINF	        _T("DateInfo")

#define DEFINE_XML_POLLPLAN_TIMECFG	        _T("TimeConfig")
#define DEFINE_XML_POLLPLAN_TIMEINFO	    _T("TimeInfo")

#define DEFINE_XML_POLLPLAN_TIMEST	        _T("StartTime")
#define DEFINE_XML_POLLPLAN_TIMEEND	        _T("EndTime")


#define DEFINE_XML_POLLPLAN_POSCFG	        _T("PosConfig")
#define DEFINE_XML_POLLPLAN_POSINFO	        _T("PosInfo")
enum
{
	WM_CHANGESCALE = WM_USER + 50,
	WM_UPDATESNAPINFO,
	WM_POLLSNAPVIDEO,
	WM_POLLREFRESH,
	WM_POLLINMIDITE,
	WM_POLLNEXTPLAN,
};

typedef struct tagPosInfo
{
	LONG nPosNum;							// 点位ID
	LONG nParentID;							// 点位所属的分组ID
	std::string strPosID;					// 点位编号
	std::string strPosName;					// 点位名称
	std::string strGB28181ID;				// 点位的国标编号
	std::string strChannelNum;				// 通道号
	std::string strGroup;
}Pos_Info, lpPos_Info;

typedef struct tagImageInfo
{
	WORD	BYT_COLOR_CAST;
	WORD    BYT_CLARITY;
	WORD	BYT_BRIGHT;
	WORD	BYT_NOISE;
	WORD	BYT_WAVE;
	WORD	BYT_MOVED;
	WORD	BYT_FREEZE;
	WORD	BYT_SIGNAL;
	tagImageInfo()
	{
		BYT_COLOR_CAST = 0;
		BYT_CLARITY = 0;
		BYT_BRIGHT = 0;
		BYT_NOISE = 0;
		BYT_WAVE = 0;
		BYT_MOVED = 0;
		BYT_FREEZE = 0;
		BYT_SIGNAL = 0;

	};

} IMAGECOMPARE;
typedef struct tagPlanInfo
{
	WORD		wInterval;
	WORD		wVidCount;
	WORD		wType;
	WORD		wPlayCount;
	WORD		wSwitch;
	WORD		wSnapFlag;
	std::string strPlanName;
	std::string strPlanID;
	std::string strDateInfo;
	std::list<std::string> strTimeList;
	std::list<tagPosInfo>lstDevice;
	IMAGECOMPARE compare;

	tagPlanInfo()
	{
		wInterval = 0;
		wVidCount = 1;
		wType = 0;
		wPlayCount = 0;
		wSwitch = 0;
		wSnapFlag = 0;
		strPlanID = "";
		strPlanName = "";
		strDateInfo = "";
		strTimeList.clear();
		lstDevice.clear();
	};

	void InitData();

} PLANINFO, *LP_PLANINFO;



class CPollDataCfg
{
public:
	CPollDataCfg();
	~CPollDataCfg();
public:
	bool SetDataPath(std::string strPath);
	void SaveXML(std::string strXml);
	void ReadXML(std::string strXml);
	bool InitData();

	std::list<PLANINFO> GetPlanList();

	bool FindFileFromDir(std::string mainDir, std::vector<std::string> &files);
private:
	std::list<PLANINFO>  m_tPlanDateList;
	std::string m_strCfgPath;
};

