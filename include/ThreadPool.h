#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "Semaphore.h"
#include "mutex.h"
#include "thread.h"
#include "condition.h"
#include <deque>
#include <set>
#include <string>
/**  
//Ïß³Ì³Ø
**/ 
class ITask; 

namespace THINK{


class CThreadPool : public Runnable
{	

public:  

	CThreadPool(const std::string&);  

	~CThreadPool();  

private:  
	//disable assign and copy

	CThreadPool(CThreadPool const&);	

	CThreadPool& operator = (CThreadPool const&);  

public:  

	int initPool(int nThread);  

	int addTask(ITask* task);  

	int destory();  

	private:  

	void run(CThread *thread, void *arg);	

private:  
	std::string m_name;

	int m_iThreadNum;  

	CMutex m_taskMutex;	

	CMutex m_threadMutex;  

	CThreadCond m_threadCond;		

	std::deque<ITask*> m_vecTask;	

	std::set<CThread*> m_setBusyThread;	 

	std::set<CThread*> m_setIdleThread;	 
    
        bool m_running;
};  

}//end of THINK
#endif
