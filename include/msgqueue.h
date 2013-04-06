#ifndef _THINK_MSGQUEUE_H
#define _THINK_MSGQUEUE_H

#include <list>
#include "types.h"
#include "mutex.h"
#include "condition.h"
#include "pool_allocator.h"

namespace THINK{ 

template <class T>
class CMsgQueue
{
public:
	typedef std::list<T, pool_allocator<T> > MSGQUEUE;
	
	CMsgQueue(int size = 128) : m_cond(m_Mutex)
	{
		m_nMaxMsg = size;
		m_nMsg = 0;
	}
	~CMsgQueue(){};

	BOOL push(T * msg, int waittime = 0)
	{
		CGuard guard(m_Mutex);
	
		if( m_nMsg >= m_nMaxMsg )
		{
			if (!waittime || m_cond.wait(waittime) == false)
			{
				return FALSE;
			}
			
		}

		m_msg_queue.push_back(*msg);
		
		m_nMsg++;

		return TRUE;
	}
	BOOL pop(T * msg_tmp)
	{
	
		CGuard guard(m_Mutex);
		
		if( m_msg_queue.empty() )
		{
			return FALSE;
		}

		assert( m_nMsg );

		*msg_tmp = m_msg_queue.front();
		m_msg_queue.pop_front();
		m_nMsg--;
		
		if (m_nMsg <= m_nMaxMsg)
		{
			m_cond.broadcast();
		}
		return TRUE;		
	}

	int size()	//获取已有的消息数目
	{
		CGuard guard(m_Mutex);
		return m_nMsg;
	}

	
private:
	int m_nMsg;
	int m_nMaxMsg;
	CThreadCond m_cond;
	CMutex m_Mutex;
	MSGQUEUE m_msg_queue;
};

} //end of namespace

#endif //_THINK_MSGQUEUE_H

