#ifndef _THINK_UNKOWN_H_
#define _THINK_UNKOWN_H_

namespace THINK{
          
class CComponentHelper;
/// �������
class IUnknown
{
    friend class CComponentHelper;
public:
    IUnknown(void);
	/// ��������
	virtual ~IUnknown(void);

	/// ���ٺ���
	virtual void destroy() = 0;

	/// �������ã����ص�ǰ��������
	virtual int addRef(void);
   
   /// �������ã����ص�ǰ��������
	virtual int release(void);

private:
	struct UnknownInternal;
	UnknownInternal	*m_internal;
};


/// �����������
class IFactoryUnknown
{
public:
	virtual ~IFactoryUnknown(){};

	
	/// \return ʵ����ID����һ�������ַ���
	virtual const char* clsid() = 0;

	/// ע�ắ������Ҫÿ�������ʼ��ʱ���ô˺����Թ�������ע��
	/// \param iid ����ӿ�ID, ����ʹ�ø��Ե�IFactory::iid()��̬������ȡ����
	/// \return �����Ƿ�ɹ�
	bool registerFactory(const char* iid);

	/// ע����������Ҫÿ������˳�ʱ���ô˺����Թ�������ע��
	/// \param iid ����ӿ�ID, ����ʹ�ø��Ե�IFactory::iid()��̬������ȡ����
	/// \return �����Ƿ�ɹ�
	bool unregisterFactory(const char* iid);
	
	
	
};

}
#endif
