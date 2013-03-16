#ifndef _COMPONENT_HELPER_H_
#define _COMPONENT_HELPER_H_

#include "unknown.h"

namespace THINK {


////////////////////////////////////////////////////////////////////////////////

/// ������������࣬�����ڲ�ʹ��
class CComponentHelper
{
public:
	/// ��ȡ��������������ڲ�ʹ��
	static IFactoryUnknown* getComponentFactory(
		const char* iid, const char* clsid);

	/// �������ü���, ���ɶ���ָ��, for getComponentInstance
//	static IUnknown* makeComponentInstance(IUnknown*);

	/// �������ü���, ���ɶ���ָ��, for createComponentObject
//	static IUnknown* makeComponentObject(IUnknown*);

	/// �������ü����������ڲ�ʹ��
	static int addRef(IUnknown*);

	/// �������ü����������ڲ�ʹ��
	static int release(IUnknown*);


};



} // namespace THINK

#endif // _COMPONENT_HELPER_H_
