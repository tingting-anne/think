#ifndef _GUARD_H_
#define _GUARD_H_

#include <stdio.h>
#include "mutex.h"
namespace THINK{
///\brief �ػ����࣬�������б����Ż����Զ��ͷ���
class CGuard
{
public:
	///\brief ���캯��
	inline explicit CGuard(CMutex& Mutex)
		:m_Mutex(Mutex)
	{
		m_Mutex.Enter();
	}
	
	///\brief ��������
	inline ~CGuard()
	{
		m_Mutex.Leave();
	}

private:
	CMutex &m_Mutex;
	//disable assign and copy
private:
	CGuard(CGuard&);
	CGuard& operator=(const CGuard&);
};
} // end of THINK
#endif //_GUARD_H_
