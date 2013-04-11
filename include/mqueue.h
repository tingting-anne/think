#ifndef _THINK_MSGQUEUE_H
#define _THINK_MSGQUEUE_H

#include <list>
#include "types.h"
#include "mutex.h"
#include "pool_allocator.h"

namespace THINK{ 

template <class T>
class CMsgQueue
{
public:
	typedef std::list<T, pool_allocator<T> > MSGQUEUE;
	
	CMsgQueue()
	{
		m_nMsg = 0;
	}
	~CMsgQueue(){};

	BOOL push(T msg)
	{
		CGuard guard(m_Mutex);
	
		_queue.push_back(msg);
		
		m_nMsg++;

		return TRUE;
	}
	BOOL pop(T* msg)
	{
	
		CGuard guard(m_Mutex);
		
		if( _queue.empty() )
		{
			return FALSE;
		}

		assert( m_nMsg );

		*msg = _queue.front();
		_queue.pop_front();
		m_nMsg--;

		return TRUE;		
	}
	
	void  splice(CMsgQueue<T> &other)
	{
		CGuard guard(m_Mutex);
		other.m_Mutex.Enter();
		_queue.splice(_queue.end(), other._queue);
		other.m_Mutex.Leave();
		
	}
	int size()	//获取已有的消息数目
	{
		CGuard guard(m_Mutex);
		return m_nMsg;
	}
	
	
private:
	int m_nMsg;
	CMutex m_Mutex;
	MSGQUEUE _queue;
};

} //end of namespace

#endif //_THINK_MSGQUEUE_H

