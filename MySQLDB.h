/**********************************************************
 * Name: MySQLDB.h
 * note: MYSQL���ݿ������װ��
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

typedef std::map<std::string,std::string> MySQLRow;       //�洢һ�����ݵĽ��
typedef std::map<unsigned long,MySQLRow> MySQLResultSet;  //�洢��ѯ�����н����

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


//���ݿ����Ӳ����ṹ��
typedef struct _MYSQL_CONNECTION
{
	std::string	dbhost;    //���ݿ��������IP
	unsigned short dbport; //����˿�
	std::string dbname;    //���ݿ���
	std::string dbuser;    //�û���
	std::string dbpass;    //����
	_MYSQL_CONNECTION()
	{
		dbport=3306;       //Ĭ�϶˿�
	};
}MYSQL_CONNECTION;

//---------------------------------------------------------------------------------------
// MySQL���ݿ�����
class MySQLDB
{
public:
	MySQLDB(void);
	virtual ~MySQLDB(void);

	/************************************************************************/
	/*�������ݿ⣬Ĭ�Ͼ��ô����ӣ�
	����˵����
	SingleConnection���������Ӳ������ο���ṹ��˵�� 
	bUTF8�� �Ƿ���UTF-8��һ�㰴Ĭ��
	bStoreResult����ѯ���������Ƿ񱣴浽���أ�Ĭ�ϲ����棬�ٶȸ����ڴ����*/
	/************************************************************************/
	bool Connect(const MYSQL_CONNECTION& SingleConnection,bool bUTF8=false,bool bStoreResult=false);
	bool Connect(LPCTSTR  lpszIP,USHORT usPort,LPCTSTR  lpszName,LPCTSTR  lpszUser,LPCTSTR  lpszPass,bool bUTF8=false,bool bStoreResult=false);
	//����Ҫ�ô�����
	bool Connect(MYSQL_CONNECTION WriteConnection,MYSQL_CONNECTION ReadConnection,bool bUTF8=false,bool bStoreResult=false);
	void Disconnect(void);

	/*********************************************************
	 * ������ݿ�(������ݿ�û���������Զ�����)
	 *********************************************************/
	bool CheckDB(void);

	/*********************************************************
	 * ѡ�����ݿ�
	 *********************************************************/
	void SelectDB(const std::string& strDBName);

	/*********************************************************
	 * ����SQL���
	 *********************************************************/
	std::string CreateSQL(const char* cszSQL,...);

	/*********************************************************
	 * ִ��SQL���(INSERT/UPDATE/DELETE)
	 * �������ִ�к�Ӱ�������,���Ϊ-1���ʾִ�д���
	 *********************************************************/
	int SQLExecute(const std::string& strSQL);
	int SQLExecute(LPCSTR strSQL);

	/*********************************************************
	 * ִ��SQL���(SELECT)
	 * �������ִ�к�Ľ����
	 *********************************************************/
	int SQLQuery(const std::string& strSQL,MySQLResultSet& res);
	int SQLQuery(LPCSTR pSql,MySQLResultSet& res);

	/*********************************************************
	 * ���INSERT��ļ�¼ID��
	 *********************************************************/
	unsigned long GetLastInsertID(void);

	/*********************************************************
	 * Escape�ַ���
	 *********************************************************/
	const char* Escape(const std::string& strValue);

	/*********************************************************
	 * PING������
	 * ������������������Ч����0��������ִ��󣬷��ط�0ֵ��
	 * ���صķ�0ֵ����ʾMySQL�����������Ƿ��ѹرգ�
	 * ���ӿ���������ԭ���նˣ�����������ȡ�
	 *********************************************************/
	int PingSingleDB(void);
	int PingWriteDB(void);
	int PingReadDB(void);

	/*********************************************************
	 * ��÷������汾
	 * ��ʾMySQL�������汾����ֵ����ʽ���£�
	 * major_version*10000 + minor_version *100 + sub_version
	 * ���磬����5.0.12������500012
	 *********************************************************/
	unsigned long GetSingleServerVersion(void);
	unsigned long GetWriteServerVersion(void);
	unsigned long GetReadServerVersion(void);

	/*********************************************************
	 * ��ÿͻ��˰汾
	 * ��ʾMySQL�ͻ��˰汾����ֵ����ʽ���£�
	 * major_version*10000 + minor_version *100 + sub_version
	 * ���磬����5.0.12������500012
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

