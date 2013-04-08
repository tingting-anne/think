#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <semaphore.h>

namespace THINK{
class CSemaphore
{
public:
	CSemaphore(unsigned int dwInitialCount = 0)
	{
		sem_init(&m_semaphore, 0 , dwInitialCount);
	}
	~CSemaphore()
	{
	      sem_destroy(&m_semaphore);
	}

	inline int Pend()
	{
	   return sem_wait(&m_semaphore);
	}

	inline int Post()
	{
	    return sem_post(&m_semaphore);
	}

private:
	sem_t m_semaphore;
};
} //end of Semaphore
#endif //__SEMAPHORE_H__
