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

/// 获取组件工厂函数模板，仅供内部使用
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

/// 获取组件单一实例，带一个组件构造参数
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
