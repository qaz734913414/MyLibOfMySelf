#ifndef __MY_POP3__
#define __MY_POP3__

#include "MyString.h"
#include "Windows.h"
#include "MailInfo.h"
#include <vector>

using namespace std;

#define DEFAULT_POP3_PORT  (110)
#define BUFFER_LEN			(513)

class CMyPOP3  
{
private:
	typedef enum
	{
		STATUS_AUTH,
		STATUS_PROCESS
	}POP3_STATUS;

public:
	typedef struct
	{
		CMyString	m_MailTitle;
		CMyString	m_MailFrom;
		CMyString	m_MailTime;
		CMyString	m_MailRecTime;
	} MailInfo;

public:
	CMyPOP3();
	virtual ~CMyPOP3();

	void	SetLoginInfo(char* user,char* password);
	void	SetPOP3Server(char* url);
	void	SetPOP3Port(int port);
	bool	startRecMail();
	int		getMailCount();
	char*	getMailTitle(int index);
	char*	getMailContent(int index);
	char*	getMailFrom(int index);
	char*	getMailTime(int index);
	char*	getMailRecTime(int index);

	char*	getErrorMessage(){return m_Buffer;}
	bool	Login();
	void	Quit();
	bool	List();
	bool	Dele(int index);
	bool	Retr(int index,CMailInfo &mail);
	bool	Reset();
	bool    Top(int index,int lineCount,CMailInfo &mail);   
	bool	Stat();

private:
	bool	ConnectServer();
	bool	User();
	bool	Pass();

	int		RecvData();
	bool    CheckRecvState();
	bool	ExcuteCmd(CMyString& cmd);

	bool	FetchListResult(CMyString& data);
	bool	FetchTopResult(CMyString& data,CMailInfo &mail);
	bool	FetchRetrResult(CMyString& data,CMailInfo &mail);
	bool    FetchMailData();
	bool	RecvCmdResult(CMyString& data);

	CMyString	m_UserName;
	CMyString	m_Password;
	CMyString	m_POP3Server;
	int			m_ServerPort;
	int			m_Socket;

	char		m_Buffer[BUFFER_LEN];

	std::vector<int>	m_MailSizeList;
	unsigned long		m_MailTotalSize;
	unsigned long		m_MailCount;

	POP3_STATUS	m_Status;
};

#endif