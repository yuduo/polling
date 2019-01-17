
#include "stdafx.h"
#include "MySQLDB.h"
#include <stdarg.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_DBMYSQL_SQLLENGTH	65535

//CSimpleLock
CSimpleLock::CSimpleLock()
{
	InitializeCriticalSection(&m_CtiticalSection);
}

CSimpleLock::~CSimpleLock()
{
	DeleteCriticalSection(&m_CtiticalSection);
}

void CSimpleLock::lock()
{
	EnterCriticalSection(&m_CtiticalSection);
}

void CSimpleLock::trylock()
{
#if(_WIN32_WINNT >= 0x0400)
	TryEnterCriticalSection(&m_CtiticalSection);
#else
	EnterCriticalSection(&m_CtiticalSection);
#endif
}

void CSimpleLock::unlock()
{
	LeaveCriticalSection(&m_CtiticalSection);
}


//CAutoLock
CAutoLock::CAutoLock(CSimpleLock *_pSLock)
	:m_pSLock(_pSLock)
{
	if (_pSLock)
	{
#if 1
		_pSLock->lock();
#else
		_pSLock->trylock();
#endif
	}
}

CAutoLock::~CAutoLock()
{
	if (m_pSLock)
	{
		m_pSLock->unlock();
	}
}
//---------------------------------------------------------------------------------------
// 构造函数
MySQLDB::MySQLDB(void)
	:m_bSingle(false)
	, m_pSingleDB(NULL)
	, m_pWriteDB(NULL)
	, m_pReadDB(NULL)
{
}

//---------------------------------------------------------------------------------------
// 析构函数
MySQLDB::~MySQLDB(void)
{
	//释放Log指针
	//ReleaseLogModule();
}

//---------------------------------------------------------------------------------------
// 连接数据库
bool MySQLDB::Connect(MYSQL_CONNECTION const & SingleConnection, bool bUTF8, bool bStoreResult)
{
	try
	{
		if (m_pSingleDB)
		{
			return true;
		}
		m_SingleConnection = SingleConnection;
		m_bUTF8 = bUTF8;
		m_bStoreResult = bStoreResult;

		//初始化数据库连接
		m_pSingleDB = mysql_init((MYSQL*)0);
		if (m_pSingleDB == NULL)
		{
			return false;
		}

		//设置自动重连
		my_bool reconnect = 1;
		mysql_options(m_pSingleDB, MYSQL_OPT_RECONNECT, &reconnect);

		//如果定义了UTF8
		if (m_bUTF8)
		{
			mysql_options(m_pSingleDB, MYSQL_SET_CHARSET_NAME, "utf8");
		}

		//连接写数据库
		if (mysql_real_connect(m_pSingleDB, m_SingleConnection.dbhost.c_str(), m_SingleConnection.dbuser.c_str(), m_SingleConnection.dbpass.c_str(), m_SingleConnection.dbname.c_str(), m_SingleConnection.dbport, NULL, 0) == NULL)
		{
			char szDBMsg[1024] = { 0 };
			sprintf_s(szDBMsg, 1024, "Connect mysql_real_connect dbhost:%s dbuser:%s dbpass:%s dbname:%s dbport:%u.\r\n", m_SingleConnection.dbhost.c_str(), m_SingleConnection.dbuser.c_str(), m_SingleConnection.dbpass.c_str(), m_SingleConnection.dbname.c_str(), m_SingleConnection.dbport);
			ShowLastError(m_pSingleDB, szDBMsg);
			return false;
		}
		m_bSingle = true;
		return true;
	}
	catch (...)
	{
		return false;
	}
}



//---------------------------------------------------------------------------------------
// 连接数据库
bool MySQLDB::Connect(LPCTSTR lpszIP, USHORT usPort, LPCTSTR  lpszName, LPCTSTR  lpszUser, LPCTSTR  lpszPass, bool bUTF8, bool bStoreResult)
{
	try
	{
		if (m_pSingleDB)
		{
			return true;
		}

		//m_SingleConnection=SingleConnection;
		m_SingleConnection.dbhost = lpszIP;
		m_SingleConnection.dbname = lpszName;
		m_SingleConnection.dbport = usPort;
		m_SingleConnection.dbpass = lpszPass;
		m_SingleConnection.dbuser = lpszUser;
		m_bUTF8 = bUTF8;
		m_bStoreResult = bStoreResult;

		//初始化数据库连接
		m_pSingleDB = mysql_init((MYSQL*)0);
		if (m_pSingleDB == NULL)
		{
			return false;
		}

		//设置自动重连
		my_bool reconnect = 1;
		mysql_options(m_pSingleDB, MYSQL_OPT_RECONNECT, &reconnect);

		//如果定义了UTF8
		if (m_bUTF8)
		{
			mysql_options(m_pSingleDB, MYSQL_SET_CHARSET_NAME, "utf8");
		}

		//连接写数据库
		if (mysql_real_connect(m_pSingleDB, m_SingleConnection.dbhost.c_str(), m_SingleConnection.dbuser.c_str(), m_SingleConnection.dbpass.c_str(), m_SingleConnection.dbname.c_str(), m_SingleConnection.dbport, NULL, 0) == NULL)
		{
			char szDBMsg[1024] = { 0 };
			sprintf_s(szDBMsg, 1024, "Connect mysql_real_connect dbhost:%s dbuser:%s dbpass:%s dbname:%s dbport:%u.\r\n", m_SingleConnection.dbhost.c_str(), m_SingleConnection.dbuser.c_str(), m_SingleConnection.dbpass.c_str(), m_SingleConnection.dbname.c_str(), m_SingleConnection.dbport);
			ShowLastError(m_pSingleDB, szDBMsg);
			return false;
		}
		m_bSingle = true;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------
// 连接数据库
bool MySQLDB::Connect(MYSQL_CONNECTION WriteConnection, MYSQL_CONNECTION ReadConnection, bool bUTF8, bool bStoreResult)
{
	try
	{
		m_WriteConnection = WriteConnection;
		m_ReadConnection = ReadConnection;
		m_bUTF8 = bUTF8;
		m_bStoreResult = bStoreResult;

		//初始化数据库连接
		m_pWriteDB = mysql_init((MYSQL*)0);
		m_pReadDB = mysql_init((MYSQL*)0);
		if (m_pWriteDB == NULL || m_pReadDB == NULL)
		{
			return false;
		}

		//设置自动重连
		my_bool reconnect = 1;
		mysql_options(m_pWriteDB, MYSQL_OPT_RECONNECT, &reconnect);
		mysql_options(m_pReadDB, MYSQL_OPT_RECONNECT, &reconnect);

		//如果定义了UTF8
		if (m_bUTF8)
		{
			mysql_options(m_pWriteDB, MYSQL_SET_CHARSET_NAME, "utf8");
			mysql_options(m_pReadDB, MYSQL_SET_CHARSET_NAME, "utf8");
		}

		//连接写数据库
		if (mysql_real_connect(m_pWriteDB, m_WriteConnection.dbhost.c_str(), m_WriteConnection.dbuser.c_str(), m_WriteConnection.dbpass.c_str(), m_WriteConnection.dbname.c_str(), m_WriteConnection.dbport, NULL, 0) == NULL)
		{
			char szDBMsg[1024] = { 0 };
			sprintf_s(szDBMsg, 1024, "Connect A mysql_real_connect dbhost:%s dbuser:%s dbpass:%s dbname:%s dbport:%u.\r\n", m_WriteConnection.dbhost.c_str(), m_WriteConnection.dbuser.c_str(), m_WriteConnection.dbpass.c_str(), m_WriteConnection.dbname.c_str(), m_WriteConnection.dbport);
			ShowLastError(m_pWriteDB, szDBMsg);
			return false;
		}
		//连接读数据库
		if (mysql_real_connect(m_pReadDB, m_ReadConnection.dbhost.c_str(), m_ReadConnection.dbuser.c_str(), m_ReadConnection.dbpass.c_str(), m_ReadConnection.dbname.c_str(), m_ReadConnection.dbport, NULL, 0) == NULL)
		{
			char szDBMsg[1024] = { 0 };
			sprintf_s(szDBMsg, 1024, "Connect B mysql_real_connect dbhost:%s dbuser:%s dbpass:%s dbname:%s dbport:%u.\r\n", m_ReadConnection.dbhost.c_str(), m_ReadConnection.dbuser.c_str(), m_ReadConnection.dbpass.c_str(), m_ReadConnection.dbname.c_str(), m_ReadConnection.dbport);
			ShowLastError(m_pReadDB, szDBMsg);
			return false;
		}
		m_bSingle = false;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------
// 断开数据库连接
void MySQLDB::Disconnect(void)
{
	try
	{
		if (m_bSingle)
		{
			mysql_close(m_pSingleDB);
			m_pSingleDB = NULL;
		}
		else
		{
			mysql_close(m_pWriteDB);
			mysql_close(m_pReadDB);
			m_pWriteDB = NULL;
			m_pReadDB = NULL;
		}
	}
	catch (...)
	{
	}
}

//---------------------------------------------------------------------------------------
// 检查数据库
bool MySQLDB::CheckDB(void)
{
	try
	{

		if (m_bSingle)
		{
			if (m_pSingleDB == NULL)
			{
				m_pSingleDB = mysql_init((MYSQL*)0);
				if (m_pSingleDB == NULL)
				{
					return false;
				}
				my_bool reconnect = 1;
				mysql_options(m_pSingleDB, MYSQL_OPT_RECONNECT, &reconnect);
				if (m_bUTF8)
				{
					mysql_options(m_pSingleDB, MYSQL_SET_CHARSET_NAME, "utf8");
				}
				if (mysql_real_connect(m_pSingleDB, m_SingleConnection.dbhost.c_str(), m_SingleConnection.dbuser.c_str(), m_SingleConnection.dbpass.c_str(), m_SingleConnection.dbname.c_str(), m_SingleConnection.dbport, NULL, 0) == NULL)
				{
					char szDBMsg[1024] = { 0 };
					sprintf_s(szDBMsg, 1024, "CheckDB A mysql_real_connect dbhost:%s dbuser:%s dbpass:%s dbname:%s dbport:%u.\r\n", m_SingleConnection.dbhost.c_str(), m_SingleConnection.dbuser.c_str(), m_SingleConnection.dbpass.c_str(), m_SingleConnection.dbname.c_str(), m_SingleConnection.dbport);
					ShowLastError(m_pSingleDB, szDBMsg);
					return false;
				}
				return true;
			}

			if (PingSingleDB() == -1) //连接断开了，直接重连
			{
				if (mysql_real_connect(m_pSingleDB, m_SingleConnection.dbhost.c_str(), m_SingleConnection.dbuser.c_str(), m_SingleConnection.dbpass.c_str(), m_SingleConnection.dbname.c_str(), m_SingleConnection.dbport, NULL, 0) == NULL)
				{
					char szDBMsg[1024] = { 0 };
					sprintf_s(szDBMsg, "CheckDB A mysql_real_connect dbhost:%s dbuser:%s dbpass:%s dbname:%s dbport:%u.\r\n", m_SingleConnection.dbhost.c_str(), m_SingleConnection.dbuser.c_str(), m_SingleConnection.dbpass.c_str(), m_SingleConnection.dbname.c_str(), m_SingleConnection.dbport);
					ShowLastError(m_pSingleDB, szDBMsg);
					return false;
				}
			}
			return true;
		}

		if (m_pWriteDB == NULL)
		{
			m_pWriteDB = mysql_init((MYSQL*)0);
			if (m_pWriteDB == NULL)
			{
				return false;
			}
			my_bool reconnect = 1;
			mysql_options(m_pWriteDB, MYSQL_OPT_RECONNECT, &reconnect);
			if (m_bUTF8)
			{
				mysql_options(m_pWriteDB, MYSQL_SET_CHARSET_NAME, "utf8");
			}
			if (mysql_real_connect(m_pWriteDB, m_WriteConnection.dbhost.c_str(), m_WriteConnection.dbuser.c_str(), m_WriteConnection.dbpass.c_str(), m_WriteConnection.dbname.c_str(), m_WriteConnection.dbport, NULL, 0) == NULL)
			{
				char szDBMsg[1024] = { 0 };
				sprintf_s(szDBMsg, "CheckDB B mysql_real_connect dbhost:%s dbuser:%s dbpass:%s dbname:%s dbport:%u.\r\n", m_WriteConnection.dbhost.c_str(), m_WriteConnection.dbuser.c_str(), m_WriteConnection.dbpass.c_str(), m_WriteConnection.dbname.c_str(), m_WriteConnection.dbport);
				ShowLastError(m_pWriteDB, szDBMsg);
				return false;
			}
		}

		if (m_pReadDB == NULL)
		{
			m_pReadDB = mysql_init((MYSQL*)0);
			if (m_pReadDB == NULL)
			{
				return false;
			}
			my_bool reconnect = 1;
			mysql_options(m_pReadDB, MYSQL_OPT_RECONNECT, &reconnect);
			if (m_bUTF8)
			{
				mysql_options(m_pReadDB, MYSQL_SET_CHARSET_NAME, "utf8");
			}
			if (mysql_real_connect(m_pReadDB, m_ReadConnection.dbhost.c_str(), m_ReadConnection.dbuser.c_str(), m_ReadConnection.dbpass.c_str(), m_ReadConnection.dbname.c_str(), m_ReadConnection.dbport, NULL, 0) == NULL)
			{
				char szDBMsg[1024] = { 0 };
				sprintf_s(szDBMsg, "CheckDB C mysql_real_connect dbhost:%s dbuser:%s dbpass:%s dbname:%s dbport:%u.\r\n", m_ReadConnection.dbhost.c_str(), m_ReadConnection.dbuser.c_str(), m_ReadConnection.dbpass.c_str(), m_ReadConnection.dbname.c_str(), m_ReadConnection.dbport);
				ShowLastError(m_pReadDB, szDBMsg);
				return false;
			}
		}
		return true;

	}
	catch (...)
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------
// 选择数据库
void MySQLDB::SelectDB(const std::string& strDBName)
{
	try
	{
		if (m_bSingle)
		{
			if (mysql_select_db(m_pSingleDB, strDBName.c_str()) != 0)
			{
				char szDBMsg[1024] = { 0 };
				sprintf_s(szDBMsg, "SelectDB A mysql_select_db strDBName:%s.\r\n", strDBName.c_str());
				ShowLastError(m_pSingleDB, szDBMsg);
			}
			return;
		}

		if (mysql_select_db(m_pWriteDB, strDBName.c_str()) != 0)
		{
			char szDBMsg[1024] = { 0 };
			sprintf_s(szDBMsg, "SelectDB B mysql_select_db strDBName:%s.\r\n", strDBName.c_str());
			ShowLastError(m_pWriteDB, szDBMsg);
		}
		if (mysql_select_db(m_pReadDB, strDBName.c_str()) != 0)
		{
			char szDBMsg[1024] = { 0 };
			sprintf_s(szDBMsg, "SelectDB C mysql_select_db strDBName:%s.\r\n", strDBName.c_str());
			ShowLastError(m_pReadDB, szDBMsg);
		}
	}
	catch (...)
	{
	}
}

//---------------------------------------------------------------------------------------
// 创建SQL语句
std::string MySQLDB::CreateSQL(const char* cszSQL, ...)
{

	char szSQL[MAX_DBMYSQL_SQLLENGTH] = { 0 };
	try
	{
		va_list args;
		va_start(args, cszSQL);
#ifdef WIN32
		_vsnprintf_s(szSQL, sizeof(szSQL), cszSQL, args);
#else
		vsnprintf(szSQL, sizeof(szSQL), cszSQL, args);
#endif
		va_end(args);
	}
	catch (...)
	{
	}
	return szSQL;
}

//---------------------------------------------------------------------------------------
// 执行SQL语句
int MySQLDB::SQLExecute(const std::string& strSQL)
{
	try
	{
		CAutoLock  csLock(&m_csDB);
		if (!CheckDB())
		{
			return -1;
		}
		if (m_bSingle)
		{
			if (m_pSingleDB == false)
			{
				return -1;
			}

			//Execute
			mysql_query(m_pSingleDB, strSQL.c_str());
			int nErrNo = mysql_errno(m_pSingleDB);
			if (nErrNo != 0)
			{
				ShowLastError(m_pSingleDB, strSQL);
				return -1;
			}
			return mysql_affected_rows(m_pSingleDB);
		}

		//写操作
		if (m_pWriteDB == false)
		{
			return -1;
		}

		//Execute
		mysql_query(m_pWriteDB, strSQL.c_str());
		int nErrNo = mysql_errno(m_pWriteDB);
		if (nErrNo != 0)
		{
			ShowLastError(m_pWriteDB, strSQL);
			return -1;
		}
		return mysql_affected_rows(m_pWriteDB);
	}
	catch (...)
	{
		//GetLogModule()->WriteLogToFile("SQLExecute异常1：" + strSQL);
		return -1;
	}
}

int MySQLDB::SQLExecute(LPCSTR strSQL)
{

	try
	{

		CAutoLock  csLock(&m_csDB);
		if (m_bSingle)
		{
			if (m_pSingleDB == false)
			{
				return -1;
			}

			//Execute
			mysql_query(m_pSingleDB, strSQL);
			int nErrNo = mysql_errno(m_pSingleDB);
			if (nErrNo != 0)
			{
				ShowLastError(m_pSingleDB, strSQL);
				return -1;
			}
			return mysql_affected_rows(m_pSingleDB);
		}

		//写操作
		if (m_pWriteDB == false)
		{
			return -1;
		}

		//Execute
		mysql_query(m_pWriteDB, strSQL);
		int nErrNo = mysql_errno(m_pWriteDB);
		if (nErrNo != 0)
		{
			ShowLastError(m_pWriteDB, strSQL);
			return -1;
		}
		return mysql_affected_rows(m_pWriteDB);
	}
	catch (...)
	{
		//GetLogModule()->WriteLogToFile("SQLExecute异常2：" + *strSQL);
		return -1;
	}
}

//---------------------------------------------------------------------------------------
int MySQLDB::SQLQuery(const std::string& strSQL, MySQLResultSet& res)
{

	try
	{
		CAutoLock  csLock(&m_csDB);
		res.clear();
		MYSQL_RES* mysql_res = NULL;

		if (m_bSingle)
		{
			if (m_pSingleDB == false)
			{
				return 0;
			}

			//Query
			mysql_real_query(m_pSingleDB, strSQL.c_str(), strSQL.length());
			int nErr = mysql_errno(m_pSingleDB);
			//if(mysql_errno(m_pSingleDB)!=0)
			if (nErr != 0)
			{
				ShowLastError(m_pSingleDB, strSQL);
				return 0;
			}


			if (m_bStoreResult)
			{
				mysql_res = mysql_store_result(m_pSingleDB);
			}
			else
			{
				mysql_res = mysql_use_result(m_pSingleDB);
			}

			if (mysql_errno(m_pSingleDB) != 0)
			{
				ShowLastError(m_pSingleDB, strSQL);
				return 0;
			}

			if (mysql_res == NULL)
			{
				return 0;
			}
		}
		else
		{
			if (m_pReadDB == false)
			{
				return 0;
			}

			//Query
			mysql_real_query(m_pReadDB, strSQL.c_str(), strSQL.length());
			if (mysql_errno(m_pReadDB) != 0)
			{
				ShowLastError(m_pReadDB, strSQL);
				return 0;
			}

			if (m_bStoreResult)
			{
				mysql_res = mysql_store_result(m_pReadDB);
			}
			else
			{
				mysql_res = mysql_use_result(m_pReadDB);
			}

			if (mysql_errno(m_pReadDB) != 0)
			{
				ShowLastError(m_pReadDB, strSQL);
				return 0;
			}

			if (mysql_res == NULL)
			{
				return 0;
			}
		}

		MYSQL_FIELD* mysql_field = mysql_fetch_fields(mysql_res);
		unsigned int mysql_field_num = mysql_num_fields(mysql_res);
		MYSQL_ROW mysql_row;
		unsigned int i = 0;
		while (mysql_row = mysql_fetch_row(mysql_res))
		{
			MySQLRow row;
			for (unsigned int j = 0; j < mysql_field_num; j++)
			{
				row[mysql_field[j].name] = (mysql_row[j]) ? mysql_row[j] : "";	//字段有值取值,无值取空
			
			}
			res.insert(MySQLResultSet::value_type(i, row));
			i++;
		}
		mysql_free_result(mysql_res);

		return i;
	}
	catch (...)
	{
		//GetLogModule()->WriteLogToFile("SQLQuery异常1：" + strSQL);
		return 0;
	}
}

int MySQLDB::SQLQuery(LPCSTR pSql, MySQLResultSet& res)
{
	try
	{
		CAutoLock  csLock(&m_csDB);
		res.clear();
		MYSQL_RES* mysql_res = NULL;

		if (m_bSingle)
		{
			if (m_pSingleDB == false)
			{
				return 0;
			}

			//Query
			mysql_real_query(m_pSingleDB, pSql, strlen(pSql));
			if (mysql_errno(m_pSingleDB) != 0)
			{
				ShowLastError(m_pSingleDB, pSql);
				return 0;
			}


			if (m_bStoreResult)
			{
				mysql_res = mysql_store_result(m_pSingleDB);
			}
			else
			{
				mysql_res = mysql_use_result(m_pSingleDB);
			}

			if (mysql_errno(m_pSingleDB) != 0)
			{
				ShowLastError(m_pSingleDB, pSql);
				return 0;
			}

			if (mysql_res == NULL)
			{
				return 0;
			}
		}
		else
		{
			if (m_pReadDB == false)
			{
				return 0;
			}

			//Query
			mysql_real_query(m_pReadDB, pSql, strlen(pSql));
			if (mysql_errno(m_pReadDB) != 0)
			{
				ShowLastError(m_pReadDB, pSql);
				return 0;
			}

			if (m_bStoreResult)
			{
				mysql_res = mysql_store_result(m_pReadDB);
			}
			else
			{
				mysql_res = mysql_use_result(m_pReadDB);
			}

			if (mysql_errno(m_pReadDB) != 0)
			{
				ShowLastError(m_pReadDB, pSql);
				return 0;
			}

			if (mysql_res == NULL)
			{
				return 0;
			}
		}

		MYSQL_FIELD* mysql_field = mysql_fetch_fields(mysql_res);
		unsigned int mysql_field_num = mysql_num_fields(mysql_res);
		MYSQL_ROW mysql_row;
		unsigned int i = 0;
		while (mysql_row = mysql_fetch_row(mysql_res))
		{
			MySQLRow row;
			for (unsigned int j = 0; j < mysql_field_num; j++)
			{
				row[mysql_field[j].name] = (mysql_row[j]) ? mysql_row[j] : "";	//字段有值取值,无值取空
			}
			res.insert(MySQLResultSet::value_type(i, row));
			i++;
		}
		mysql_free_result(mysql_res);
		return i;
	}
	catch (...)
	{
		//GetLogModule()->WriteLogToFile("SQLQuery异常2：" + *pSql);
		return 0;
	}
}


//---------------------------------------------------------------------------------------
unsigned long MySQLDB::GetLastInsertID(void)
{
	try
	{

		if (m_bSingle)
		{
			return mysql_insert_id(m_pSingleDB);
		}
		return mysql_insert_id(m_pWriteDB);
	}
	catch (...)
	{
	}
}

//---------------------------------------------------------------------------------------
const char* MySQLDB::Escape(const std::string& strValue)
{
	char szValue[MAX_DBMYSQL_SQLLENGTH] = { 0 };
	try
	{
		if (m_bSingle)
		{
			mysql_real_escape_string(m_pSingleDB, szValue, strValue.c_str(), strValue.length());
		}
		else
		{
			mysql_real_escape_string(m_pReadDB, szValue, strValue.c_str(), strValue.length());
		}
	}
	catch (...) {}

	return szValue;
}

//---------------------------------------------------------------------------------------
int MySQLDB::PingSingleDB(void)
{
	try
	{
		if (m_bSingle)
		{
			return mysql_ping(m_pSingleDB);
		}
		return -1;
	}
	catch (...)
	{
		return -1;
	}
}

//---------------------------------------------------------------------------------------
int MySQLDB::PingWriteDB(void)
{
	return mysql_ping(m_pWriteDB);
}

//---------------------------------------------------------------------------------------
int MySQLDB::PingReadDB(void)
{
	return mysql_ping(m_pReadDB);
}

//---------------------------------------------------------------------------------------
unsigned long MySQLDB::GetSingleServerVersion(void)
{
	if (m_pSingleDB == NULL)
	{
		return 0;
	}
	return mysql_get_server_version(m_pSingleDB);
}

//---------------------------------------------------------------------------------------
unsigned long MySQLDB::GetWriteServerVersion(void)
{
	if (m_pWriteDB == NULL)
	{
		return 0;
	}
	return mysql_get_server_version(m_pWriteDB);
}

//---------------------------------------------------------------------------------------
unsigned long MySQLDB::GetReadServerVersion(void)
{
	if (m_pReadDB == NULL)
	{
		return 0;
	}
	return mysql_get_server_version(m_pReadDB);
}

//---------------------------------------------------------------------------------------
unsigned long MySQLDB::GetClientVersion(void)
{
	return mysql_get_client_version();
}

//---------------------------------------------------------------------------------------
void MySQLDB::ShowLastError(MYSQL* pDB, const std::string& strMysql/*=""*/)
{
	try
	{
		unsigned int nErrCode = mysql_errno(pDB);
		if (nErrCode == 0)
		{
			return;
		}
		const char* cszErrText = mysql_error(pDB);
		if (cszErrText == NULL)
		{
			return;
		}
		printf("[DBERR] %d:%s SQL=%s.\n", nErrCode, cszErrText, strMysql.c_str());
	}
	catch (...)
	{
		return;
	}
}


