#ifndef __MY_FILE__
#define __MY_FILE__
#include "MyString.h"
#include "MyDebug.h"
#include "MyIOStream.h"
#include "windows.h"

#define TEMP_BUFFER_SIZE (1000)
class CMyFile:public CMyIOStream
{
public:
	enum FILE_MODE
	{
		FILE_NEW,    //�ļ��������򴴽�,�������ʧ��
		FILE_OPEN,   //�ļ����������ʧ��
		FILE_NEW_OR_OPEN,  //�ļ��������򴴽����ļ��������
		FILE_NEW_OR_CLEAR  //�ļ���������գ��������򴴽�
	};

//	enum SEEK_MODE
//	{
//		SEEK_START,
//		SEEK_CURRENT,
//		SEEK_ENDED
//	};
public:
	CMyFile();
	virtual ~CMyFile();

	virtual int	Open(char *filePath,FILE_MODE mode);
	virtual int	read(char *buf,int size);
	virtual int	write(char *buf,int size);
	virtual int	seek(CMyIOStream::SEEK_MODE mode,int offset);
	int			Flush();
	void		DeleteFile();
	
	char*		GetMapping();
	void		ReleaseMapping();
	void        CopyToFile(char *filePath);
	unsigned long	GetFileSize();

	static int  GetUniqueFileName(char*	buf,int bufLen);
	static CMyString	GetUniqueFileName();
	static bool IsFileExist(char *filePath);
	//�ݹ�Ĵ���Ŀ¼�Լ���Ŀ¼
	static void	CreateDir(char *path);
private:
	// �ڵ���GetMapping��������ã���ס�ļ�����ʱ���ļ��Ķ�д��λ����Ч
	void		LockFile(){m_Locked=true;}        
	void		UnlockFile(){m_Locked=false;}
	bool		IsLocked(){return m_Locked;}
	void		Reset();

private:
	FILE*		m_File;      //�ļ�ָ��
	int			m_FileSize;
	void*		m_FileBuf;   //��Ϊ�ļ�ӳ�����ļ�ӳ���ַ
	HANDLE		m_FileHandle;  //�ļ����
	HANDLE		m_MapHandle;   //�ļ�ӳ����
	int 		m_Error;     //�����ʾ
	
	bool		m_Locked;

	static char	*TAG;

protected:
	CMyString   m_FilePath;
	bool        m_Inital;    //�Ƿ��Ѿ������ļ�
};
#endif