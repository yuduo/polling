#include "stdafx.h"
#include "PollDataCfg.h"
#include "tinyxml2.h"
#include <io.h>

void PLANINFO::InitData()
{
	wInterval = 0;
	wVidCount = 1;
	wType = 0;
	wPlayCount = 0;
	wSwitch = 0;
	wSnapFlag = 0;
	strPlanName = "";
	strDateInfo = "";
	strTimeList.clear();
}

CPollDataCfg::CPollDataCfg()
{
}


CPollDataCfg::~CPollDataCfg()
{
}

std::list<PLANINFO>  CPollDataCfg::GetPlanList()
{
	return m_tPlanDateList;
}

bool CPollDataCfg::InitData()
{
	bool bRet = false;
	if (m_strCfgPath.size() <= 0)
	{
		return bRet;
	}

	if (!PathFileExists(m_strCfgPath.c_str()))
	{
		return bRet;
	}

	m_tPlanDateList.clear();
	//获取所有的plan的配置
	std::vector<std::string> vlstFile;
	if (FindFileFromDir(m_strCfgPath, vlstFile))
	{
		for (std::vector<std::string>::const_iterator iter = vlstFile.cbegin(); iter != vlstFile.cend(); iter++)
		{
			ReadXML(*iter);
		}
	}

	



	return bRet;
}

bool CPollDataCfg::SetDataPath(std::string strPath)
{
	bool bRet = false;
	if (strPath.size()<=0)
	{
		return bRet;
	}

	if (!PathFileExists(strPath.c_str()))
	{
		return bRet;
	}

	m_strCfgPath = strPath;
	bRet = true;
	return bRet;
}

void CPollDataCfg::ReadXML(std::string strXml)
{

}

void CPollDataCfg::SaveXML(std::string strXml)
{
	
}


bool CPollDataCfg::FindFileFromDir(std::string mainDir, std::vector<std::string> &files)
{
	files.clear();
	if (mainDir.size() <= 0)
	{
		return false;
	}
	std::string strfind = mainDir + "\\*.xml";
	const char *dir = mainDir.c_str();
	//_chdir(dir);
	long hFile;
	_finddata_t fileinfo;
	


	if ((hFile = _findfirst(strfind.c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (!(fileinfo.attrib & _A_SUBDIR))//找到文件  
			{
				if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
					continue;


				char filename[_MAX_PATH];
				strcpy_s(filename, dir);
				strcat_s(filename, "\\");
				strcat_s(filename, fileinfo.name);
				std::string temfilename = filename;
				files.push_back(temfilename);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

	return true;
	

}