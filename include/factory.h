#ifndef _COMPONENT_FACTORY_H_
#define _COMPONENT_FACTORY_H_
/*
 *    //new
 *    T* t= getComponentInstance(a,clsid);
 *    //using
 *    t->dosth();
 *    //release
 *    t->destrory();
 * 
 * */
#include "helper.h"

namespace THINK{
#define CLSID "Local"

/// ��ȡ�����������ģ�壬�����ڲ�ʹ��
template<class T>
	inline typename T::IFactory* getComponentFactory(const char* clsid)
{
	return dynamic_cast<typename T::IFactory*>(
		CComponentHelper::getComponentFactory(T::IFactory::iid(), clsid));
}

template<class T>
inline T* getComponentInstance(
	const char* clsid = CLSID)
{
	typename T::IFactory* cf = getComponentFactory<T>(clsid);
	if (cf != NULL)
	{
		T* instance = cf->instance();
		return instance;
	}

	return NULL;
}

/// ��ȡ�����һʵ������һ������������
template<class T, class A1>
inline T* getComponentInstance(
	A1 const & a1,
	const char* clsid = CLSID)
{
	
	typename T::IFactory* cf = getComponentFactory<T>(clsid);
	if (cf != NULL)
	{
		T* instance = cf->instance(a1);
		return instance;
	}

	return NULL;
}



} // namespace THINK
#endif
