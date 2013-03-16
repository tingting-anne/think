#ifndef _THINK_UNKOWN_H_
#define _THINK_UNKOWN_H_

namespace THINK{
          
class CComponentHelper;
/// 组件基类
class IUnknown
{
    friend class CComponentHelper;
public:
    IUnknown(void);
	/// 析够函数
	virtual ~IUnknown(void);

	/// 销毁函数
	virtual void destroy() = 0;

	/// 增加引用，返回当前引用数；
	virtual int addRef(void);
   
   /// 减少引用，返回当前引用数；
	virtual int release(void);

private:
	struct UnknownInternal;
	UnknownInternal	*m_internal;
};


/// 组件工厂基类
class IFactoryUnknown
{
public:
	virtual ~IFactoryUnknown(){};

	
	/// \return 实现类ID，是一个常量字符串
	virtual const char* clsid() = 0;

	/// 注册函数，需要每个组件初始化时调用此函数对工厂进行注册
	/// \param iid 组件接口ID, 必须使用各自的IFactory::iid()静态函数获取而来
	/// \return 返回是否成功
	bool registerFactory(const char* iid);

	/// 注销函数，需要每个组件退出时调用此函数对工厂进行注销
	/// \param iid 组件接口ID, 必须使用各自的IFactory::iid()静态函数获取而来
	/// \return 返回是否成功
	bool unregisterFactory(const char* iid);
	
	
	
};

}
#endif
