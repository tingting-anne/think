
#include "ThreadPool.h"
#include "PrintLog.h"
#include <errno.h>
#include <stdio.h>
class ITask 
{
public:
 	void Run(){};
};
namespace THINK{

#define MAX_THREAD_NUM 4

CThreadPool::CThreadPool(const std::string& name): m_threadCond(m_threadMutex)
,m_running(false)
{
  m_name = name;
  m_iThreadNum = MAX_THREAD_NUM;
  m_setIdleThread.clear();
  m_vecTask.clear();
  m_setBusyThread.clear();
 
}

CThreadPool::~CThreadPool() 
{
	
  if (m_running) destory();
  

}

int CThreadPool::initPool(int nThread) 
{
  m_iThreadNum = nThread;
  m_running = true;
  CThread* _thread = NULL;
  for (int i= 0; i < m_iThreadNum; i++)
  {
	_thread = new CThread;
	_thread->start(this, (void*)((long)i));
	m_setIdleThread.insert(_thread);
  }
  return 0;
}

int CThreadPool::addTask(ITask* task) 
{
  m_taskMutex.Enter();
  m_vecTask.push_back(task);
  m_threadCond.signal();
  m_taskMutex.Leave();
  return 0;
}

void CThreadPool::run(CThread *thread, void *arg) 
{
 // pthread_t pthread_id = pthread_self();
  while(m_running) 
  {
	m_threadMutex.Enter();
	m_threadCond.wait();
	m_taskMutex.Enter();
	if (!m_vecTask.empty()) 
	{
	  ITask* task = m_vecTask.front();
	  m_vecTask.pop_front();
	  m_setBusyThread.insert(thread);
	  m_setIdleThread.erase(thread);
	 
	  m_taskMutex.Leave();
	  m_threadMutex.Leave();
	  //free mutex
	  task->Run();
	} 
	else 
	{
	  m_taskMutex.Leave();
	  m_threadMutex.Leave();
	}
  }
}

int CThreadPool::destory() 
{ 
  //wakeup all threads
  m_running = false;
  m_threadCond.broadcast();
  std::set<CThread*>::iterator iter = m_setIdleThread.begin();
  while(iter != m_setIdleThread.end()) {
	
	(*iter)->join();
	delete (*iter);
	iter++;
  }
  
  iter = m_setBusyThread.begin();
  while(iter != m_setBusyThread.end()) {
	
	(*iter)->join();
	delete (*iter);
	iter++;
  }
  
  return 0;
}
	

}

