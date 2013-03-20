// TestCom1.cpp : 定义 DLL 应用程序的入口点。
//
#ifndef _TEST_COMPONENT_H
#define _TEST_COMPONENT_H

#include "unknown.h"

class ICar : public THINK::IUnknown
{
public:
	class IFactory : public THINK::IFactoryUnknown
	{
	public:
		virtual ~ IFactory (){};
		virtual ICar* instance(const char* brand) = 0;
		virtual ICar* create(const char* brand) = 0;
	
		// 组件接口ID定义
		static const char* iid(){return "Car";};
	};

	virtual ~ICar (){};

	virtual bool startEngine( ) = 0;

	virtual bool drive( ) = 0;

	// …
};
#endif //_TEST_COMPONENT_H
