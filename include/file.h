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
		RDONLY = 0x0000, ///<只读
		WRONLY,			 ///<只写
		RDWR,            ///<读写
		WAPPEND,         ///<追加写
         
	};
	enum 
	{
		BufferLimit = 64*1024,
	};

	/// 构造函数。
	CFile();

	/// 析构函数。如果数据缓冲还有效，会被释放。
	virtual ~CFile();

	bool Open(const char* pFileName, unsigned int dwFlags = RDONLY);

	void Close();

	unsigned int Read(void *pBuffer, unsigned int dwCount);

 	unsigned int Write(void *pBuffer, unsigned int dwCount);

	unsigned int Seek(long lOff,  int whence);
	///范围文件指针位置
	unsigned int GetPos();
	///返回文件长度
	unsigned int GetLength();
	///加载到内存模式
	unsigned char* Load(const char* pFileName);
	/// 释放 
	void UnLoad();

private:
	FILE*       m_pFile;
	unsigned char* m_pBuffer;   ///文件缓冲,Load方式
	int      m_dwFlags;              ///<文件打开标记
	unsigned int m_dwLength;	///< 文件长度。
	
};
} //end of THINK
#endif 




