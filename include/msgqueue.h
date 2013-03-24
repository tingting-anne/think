#ifndef _THINK_MSGQUEUE_H
#define _THINK_MSGQUEUE_H

#include <list>
#include "types.h"
#include "mutex.h"
#include "Semaphore.h"
#include "pool_allocator.h"

namespace THINK{ 

template <class T>
class CMsgQueue
{
public:
	typedef std::list<T, pool_allocator<T> > MSGQUEUE;
	
	CMsgQueue(int size = 1024)
	{
		m_nMaxMsg = size;
		m_nMsg = 0;
	}
	~CMsgQueue(){};

	BOOL SendMessage(T * msg)
	{
		CGuard guard(m_Mutex);
	
		if( m_nMsg >= m_nMaxMsg )
		{
			return FALSE;
		}

		
		m_msg_queue.push_back(*msg);
		
		m_nMsg++;

		m_Semaphore.Post();
		return TRUE;
	}
	BOOL RecvMessage( T * msg_tmp, BOOL wait = TRUE)
	{
		if(wait)
		{
			m_Semaphore.Pend();
		}

		CGuard guard(m_Mutex);
		
		if( m_msg_queue.empty() )
		{
			return FALSE;
		}

		assert( m_nMsg );

		if(!wait)
		{
			m_Semaphore.Pend();
		}

		*msg_tmp = m_msg_queue.front();
		m_msg_queue.pop_front();
		m_nMsg--;

		return TRUE;		
	}
	BOOL ClearMessage()
	{
		int n = m_msg_queue.size();
		for(int i = 0; i < n; i++)
		{
			m_Semaphore.Pend();
			m_msg_queue.pop_front();
			m_nMsg--;
		}

		return TRUE;
	}
	int GetMessageCount()	//获取已有的消息数目
	{
		CGuard guard(m_Mutex);
		return m_nMsg;
	}
	int GetMessageSize()	//获取消息最大可有多少个结点
	{
		return m_nMaxMsg;
	}

private:
	int m_nMsg;
	int m_nMaxMsg;
	CSemaphore m_Semaphore;
	CMutex m_Mutex;
	MSGQUEUE m_msg_queue;
};

} //end of namespace

#endif //_THINK_MSGQUEUE_H

