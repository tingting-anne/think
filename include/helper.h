#ifndef _COMPONENT_HELPER_H_
#define _COMPONENT_HELPER_H_

#include "unknown.h"

namespace THINK {


////////////////////////////////////////////////////////////////////////////////

/// 组件对象助手类，仅供内部使用
class CComponentHelper
{
public:
	/// 获取组件工厂，仅供内部使用
	static IFactoryUnknown* getComponentFactory(
		const char* iid, const char* clsid);

	/// 处理引用计数, 生成对象指针, for getComponentInstance
//	static IUnknown* makeComponentInstance(IUnknown*);

	/// 处理引用计数, 生成对象指针, for createComponentObject
//	static IUnknown* makeComponentObject(IUnknown*);

	/// 增加引用计数，仅供内部使用
	static int addRef(IUnknown*);

	/// 减少引用计数，仅供内部使用
	static int release(IUnknown*);


};



} // namespace THINK

#endif // _COMPONENT_HELPER_H_
