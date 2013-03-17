#include "file.h"
#include <assert.h>

namespace THINK{

CFile::CFile()
{
	m_pFile = NULL;
	m_pBuffer = NULL;
	m_dwFlags = 0;
	m_dwLength = 0;
}

CFile::~CFile()
{
	if(m_pFile)
	{
		Close();
	}
	if(m_pBuffer)
	{
		UnLoad();
	}
}

bool CFile::Open(const char* pFileName, unsigned int dwFlags)
{
	if (!pFileName)
	{
                   
		return false;
	}
	const char* mode = "";
	switch(dwFlags)
	{
		case RDONLY:
			mode = "r";
			break;
		case WRONLY:
			mode = "w";
			break;
		case RDWR:
			mode = "r+";
			break;
		case WAPPEND:
             mode = "a";
             break; 
		default:
			return false;
	}
	
	m_pFile = fopen(pFileName, mode);
	if (!m_pFile)
	{
		return false;
	}

	return true;
}

void CFile::Close()
{
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
}

unsigned int CFile::Read(void *pBuffer, unsigned int dwCount)
{
	if (!m_pFile)
	{
		return 0;
	}
	return fread(pBuffer, 1, dwCount , m_pFile);
}

unsigned int CFile::Write(void *pBuffer, unsigned int dwCount)
{
	if (!m_pFile)
	{
		return 0;
	}
	return fwrite(pBuffer, 1, dwCount, m_pFile);
}

unsigned int CFile::Seek(long lOff,  int whence)
{
	if (!m_pFile)
	{
		return 0;
	}
	int pos = fseek(m_pFile, lOff, whence);
	if (pos == 0)
	{
		return GetPos();
	}
	return 0;
}

unsigned int CFile::GetPos()
{
	if (!m_pFile)
	{
		return 0;
	}
	int pos = ftell(m_pFile);
   
	return (pos == -1)? 0 : pos;
}

unsigned int CFile::GetLength()
{
  
  unsigned int oldpos = GetPos();
	Seek(0, SEEK_END);
	
	m_dwLength = GetPos();
	
	Seek(oldpos, SEEK_SET);

	return m_dwLength;
}

unsigned char* CFile::Load(const char* pFileName)
{
	int ret;
	if (Open(pFileName, RDONLY) == false)
	{
		return NULL;
	}
	int length = GetLength();
    
	if (length > 10 * BufferLimit) 
		return NULL;

	m_pBuffer = new unsigned char[length];

	if(m_pBuffer)
	{
		Seek(0, SEEK_SET);
		ret = Read(m_pBuffer, length);
		assert(ret == length);
	}

	Close();

	return m_pBuffer;

}

void CFile::UnLoad()
{
	if(m_pBuffer)
	{
		delete []m_pBuffer;
		m_pBuffer = NULL;
	}
}
}
