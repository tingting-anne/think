#include "unknown.h"
#include "Guard.h"
#include "helper.h"
#include "atomic.h"
#include <map>
#include <string>

namespace THINK{
////////////////////////////////////////////////////////////////////


struct IUnknown::UnknownInternal
{
	atomic_t ref;
	bool isUsing;
	bool instance;

	UnknownInternal() : ref(1), isUsing(false), instance(false) {}
};

IUnknown::IUnknown()
{
	m_internal = new IUnknown::UnknownInternal;
}

IUnknown::~IUnknown()
{
	delete m_internal;
}

int IUnknown::addRef(void)
{
     atomic_add(1, &m_internal->ref);
	return atomic_read(&m_internal->ref);
	
}

int IUnknown::release(void)
{
	//int ref = --m_internal->ref;
    int ref = atomic_sub(1, &m_internal->ref);
	if (ref == 0)
	{
       destroy();
	}

	return ref;
}

typedef std::map<std::string, IFactoryUnknown*> FactoryMap;
typedef std::map<std::string, FactoryMap> SystemMap;


static SystemMap s_interfaces;
static CMutex s_mutex;

bool IFactoryUnknown::registerFactory(const char* iid)
{
	//register factory
	CGuard guard(s_mutex);

	s_interfaces[iid][clsid()] = this;

	return true;
}

bool IFactoryUnknown::unregisterFactory(const char* iid)
{
	CGuard guard(s_mutex);

	s_interfaces[iid][clsid()] = NULL;

	return true;
}
///iid: interface id
///clsid: class id 
IFactoryUnknown* CComponentHelper::getComponentFactory(const char* iid, const char* clsid)
{
    CGuard guard(s_mutex);

	/// ��ȡҵ������Ĺ���ʵ��
	SystemMap::iterator pi;
	if((pi = s_interfaces.find(iid)) == s_interfaces.end())
	{
        printf("component Interface Not Found!\n");
		return NULL;
	}

	FactoryMap::iterator pj;
	if((pj = (*pi).second.find(clsid)) == (*pi).second.end())
	{
		printf("component Class Not Found!\n");
		return NULL;
	} 
    return (*pj).second; //���ع���        
}

int CComponentHelper::addRef(IUnknown* ptr)
{
	return ptr ? ptr->addRef() : 0;
}

int CComponentHelper::release(IUnknown* ptr)
{
	return ptr ? ptr->release() : 0;
}

}//end of namespace 
