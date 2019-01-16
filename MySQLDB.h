/**********************************************************
 * Name: MySQLDB.h
 * note: MYSQL数据库操作封装库
 **********************************************************/

#pragma once

#include <map>
#include <string>
#include <atlstr.h>

#include <winsock2.h>
//#ifdef DBAPI_EXPORTS
//#define EXT_CLASS _declspec(dllexport)
//#else
//#define EXT_CLASS _declspec(dllimport)
//#endif
#ifdef WIN32
#include "include/mysql/mysql.h"
#else
#include "mysql.h"
#endif

typedef std::map<std::string,std::string> MySQLRow;       //存储一排数据的结果
typedef std::map<unsigned long,MySQLRow> MySQLResultSet;  //存储查询的所有结果集

#pragma comment(lib, "libmysql.lib")

#pragma pack(1)

class CSimpleLock
{
public:
	CSimpleLock();
	virtual ~CSimpleLock();
	
public:
	void lock();
	void trylock();
	void unlock();
	
private:
	CRITICAL_SECTION 	m_CtiticalSection;
};

class CAutoLock
{
public:
	CAutoLock(CSimpleLock *_pSLock);
	virtual ~CAutoLock();

private:
	CSimpleLock *m_pSLock;
};


//数据库连接参数结构体
typedef struct _MYSQL_CONNECTION
{
	std::string	dbhost;    //数据库服务主机IP
	unsigned short dbport; //服务端口
	std::string dbname;    //数据库名
	std::string dbuser;    //用户名
	std::string dbpass;    //密码
	_MYSQL_CONNECTION()
	{
		dbport=3306;       //默认端口
	};
}MYSQL_CONNECTION;

//---------------------------------------------------------------------------------------
// MySQL数据库驱动
class MySQLDB
{
public:
	MySQLDB(void);
	virtual ~MySQLDB(void);

	/************************************************************************/
	/*连接数据库，默认就用此连接，
	参数说明：
	SingleConnection：数据连接参数，参考其结构体说明 
	bUTF8： 是否用UTF-8，一般按默认
	bStoreResult：查询到的数据是否保存到本地，默认不保存，速度更快内存更少*/
	/************************************************************************/
	bool Connect(const MYSQL_CONNECTION& SingleConnection,bool bUTF8=false,bool bStoreResult=false);
	bool Connect(LPCTSTR  lpszIP,USHORT usPort,LPCTSTR  lpszName,LPCTSTR  lpszUser,LPCTSTR  lpszPass,bool bUTF8=false,bool bStoreResult=false);
	//不需要用此连接
	bool Connect(MYSQL_CONNECTION WriteConnection,MYSQL_CONNECTION ReadConnection,bool bUTF8=false,bool bStoreResult=false);
	void Disconnect(void);

	/*********************************************************
	 * 检查数据库(如果数据库没有连接则自动连接)
	 *********************************************************/
	bool CheckDB(void);

	/*********************************************************
	 * 选择数据库
	 *********************************************************/
	void SelectDB(const std::string& strDBName);

	/*********************************************************
	 * 创建SQL语句
	 *********************************************************/
	std::string CreateSQL(const char* cszSQL,...);

	/*********************************************************
	 * 执行SQL语句(INSERT/UPDATE/DELETE)
	 * 返回语句执行后影响的行数,如果为-1则表示执行错误
	 *********************************************************/
	int SQLExecute(const std::string& strSQL);
	int SQLExecute(LPCSTR strSQL);

	/*********************************************************
	 * 执行SQL语句(SELECT)
	 * 返回语句执行后的结果集
	 *********************************************************/
	int SQLQuery(const std::string& strSQL,MySQLResultSet& res);
	int SQLQuery(LPCSTR pSql,MySQLResultSet& res);

	/*********************************************************
	 * 获得INSERT后的记录ID号
	 *********************************************************/
	unsigned long GetLastInsertID(void);

	/*********************************************************
	 * Escape字符串
	 *********************************************************/
	const char* Escape(const std::string& strValue);

	/*********************************************************
	 * PING服务器
	 * 如果与服务器的连接有效返回0。如果出现错误，返回非0值。
	 * 返回的非0值不表示MySQL服务器本身是否已关闭，
	 * 连接可能因其他原因终端，如网络问题等。
	 *********************************************************/
	int PingSingleDB(void);
	int PingWriteDB(void);
	int PingReadDB(void);

	/*********************************************************
	 * 获得服务器版本
	 * 表示MySQL服务器版本的数值，格式如下：
	 * major_version*10000 + minor_version *100 + sub_version
	 * 例如，对于5.0.12，返回500012
	 *********************************************************/
	unsigned long GetSingleServerVersion(void);
	unsigned long GetWriteServerVersion(void);
	unsigned long GetReadServerVersion(void);

	/*********************************************************
	 * 获得客户端版本
	 * 表示MySQL客户端版本的数值，格式如下：
	 * major_version*10000 + minor_version *100 + sub_version
	 * 例如，对于5.0.12，返回500012
	 *********************************************************/
	unsigned long GetClientVersion(void);
	
protected:
	MYSQL*		m_pSingleDB;
	MYSQL*		m_pWriteDB;
	MYSQL*		m_pReadDB;
	void ShowLastError(MYSQL* pDB,const std::string& strMysql="");

private:
	bool				m_bSingle;
	MYSQL_CONNECTION	m_SingleConnection;
	MYSQL_CONNECTION	m_WriteConnection;
	MYSQL_CONNECTION	m_ReadConnection;
	bool				m_bUTF8;
	bool				m_bStoreResult;
	
	CSimpleLock			m_csDB;
};

