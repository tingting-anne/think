#ifndef __MUTEX_H__
#define __MUTEX_H__
#ifndef WIN32
#include <pthread.h> 
#endif
#include <assert.h>
#include <errno.h>
namespace THINK{
/// 互斥量类型
enum mutex_type
{
	MUTEX_NORMAL = 0,
	MUTEX_ERRORCHECK = 1,
	MUTEX_RECURSIVE = 2,
	MUTEX_DEFAULT = 3,
	
};
class CMutex
{
public:
	CMutex(int nType = MUTEX_NORMAL) : m_Type(nType)
	{
		pthread_mutexattr_t  attr;
		if (pthread_mutexattr_init(&attr)) 
		{
		   assert(0);
		}
		else if (pthread_mutexattr_settype(&attr, nType))
		{
		   assert(0);
		}
		else if (pthread_mutex_init(&m_Mutex,&attr))  /*初始化互斥量*/
		{
		   assert(0);
		}
		pthread_mutexattr_destroy(&attr);
	}

	~CMutex()
	{
		pthread_mutex_destroy(&m_Mutex);
	}
	
	bool  Locked()
	{
		int ret = pthread_mutex_trylock(&m_Mutex);

		if (ret == EBUSY) 
		{
			return true;
		}
		else if (ret) 
		{
			//printf("try lock failed!\n");
			return false;	
		} 
		else 
		{
			pthread_mutex_unlock(&m_Mutex);
		}

		return false;
	}
	
	bool Enter()
	{
	        return pthread_mutex_lock(&m_Mutex) == 0 ? true:false;
	}
	
	bool Leave()
	{
		//assert(m_Mutex);
		return pthread_mutex_unlock(&m_Mutex) == 0 ? true:false;
	}
	int getMutexType() const
	{
		return m_Type;
	}
	pthread_mutex_t*  getMutex() 
	{
		return &m_Mutex;
	}
private:
	pthread_mutex_t m_Mutex;
	int				m_Type;
	// disable assign and copy
private:
	//CMutex( const CMutex & );
//	CMutex &operator=( const CMutex & );
};
} //end of namespace
#endif //__MUTEX_H__

