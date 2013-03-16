#ifndef _BASE_FILE_H_
#define _BASE_FILE_H_
#include <stdio.h>
//#include <sys/types.h>
#include <unistd.h>


namespace THINK{

class CFile 
{
public:
	enum OpenFlags
	{
		RDONLY = 0x0000, ///<ֻ��
		WRONLY,			 ///<ֻд
		RDWR,            ///<��д
		WAPPEND,         ///<׷��д
         
	};
	enum 
	{
		BufferLimit = 64*1024,
	};

	/// ���캯����
	CFile();

	/// ����������������ݻ��廹��Ч���ᱻ�ͷš�
	virtual ~CFile();

	bool Open(const char* pFileName, unsigned int dwFlags = RDONLY);

	void Close();

	unsigned int Read(void *pBuffer, unsigned int dwCount);

 	unsigned int Write(void *pBuffer, unsigned int dwCount);

	unsigned int Seek(long lOff,  int whence);
	///��Χ�ļ�ָ��λ��
	unsigned int GetPos();
	///�����ļ�����
	unsigned int GetLength();
	///���ص��ڴ�ģʽ
	unsigned char* Load(const char* pFileName);
	/// �ͷ� 
	void UnLoad();

private:
	FILE*       m_pFile;
	unsigned char* m_pBuffer;   ///�ļ�����,Load��ʽ
	int      m_dwFlags;              ///<�ļ��򿪱��
	unsigned int m_dwLength;	///< �ļ����ȡ�
	
};
} //end of THINK
#endif 




