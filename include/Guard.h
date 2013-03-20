#ifndef _GUARD_H_
#define _GUARD_H_

#include <stdio.h>
#include "mutex.h"
namespace THINK{
///\brief 守护者类，对锁进行保护优化，自动释放锁
class CGuard
{
public:
	///\brief 构造函数
	inline explicit CGuard(CMutex& Mutex)
		:m_Mutex(Mutex)
	{
		m_Mutex.Enter();
	//	printf("mutex 0x%p Enter\n", &m_Mutex);
	};
	
	///\brief 析构函数
	inline ~CGuard()
	{
		m_Mutex.Leave();
	//	printf("mutex 0x%p Leave\n", &m_Mutex);
	};

private:
	CMutex &m_Mutex;
	//disable assign and copy
private:
	CGuard(CGuard&);
	CGuard& operator=(const CGuard&);
};
} // end of THINK
#endif //_GUARD_H_
