//TestComponent

#include <stdio.h>
#include "TestComponent.h"
#include "factory.h"
#include <string>

using namespace THINK;


class CCar : public ICar
{
public:
	class CFactory : public ICar::IFactory
	{
	public:
		CFactory();
		~CFactory();
		const char* clsid(){return "Local";};
		
		ICar* instance(const char* brand) ;
		ICar* create(const char* brand) ;
	
	};

	CCar(const char* brand);

	~CCar();

	static	CCar* instance(const char* brand);

	bool startEngine( );

	bool drive( );

	void destroy();

private:
	static CCar* sm_instance;
	static int sm_objectCount;

	std::string m_brand;
	// ��
};

CCar* CCar::sm_instance = NULL;
int CCar::sm_objectCount = 0;

CCar::CFactory::CFactory()
{
	registerFactory(iid()); // ע����������͵�ID�������ID
}

CCar::CFactory::~CFactory()
{
	unregisterFactory(iid());
}


ICar* CCar::CFactory::instance(const char* brand)
{
	return CCar::instance(brand);
}

ICar* CCar::CFactory::create(const char* brand)
{
	return new CCar(brand);
}



CCar::CCar(const char* brand) : m_brand(brand)
{
	sm_objectCount++;
	printf("CCar() You have %d car(s) now\n", sm_objectCount);
}

CCar::~CCar()
{
	sm_objectCount--;
	printf("~CCar() You have %d car(s) now\n", sm_objectCount);
}

CCar* CCar::instance(const char* brand)
{
	if(!sm_instance)
	{
		sm_instance = new CCar(brand);
	}

	return sm_instance;
}

bool CCar::startEngine( )
{
	printf("engine start...\n");

	return true;
}

bool CCar::drive( )
{

	printf("drive...\n");

	return true;
}



void CCar::destroy()
{
	if(this == sm_instance)
	{
		sm_instance = NULL;//�ȸ�λ 
	}
	delete this;
}



void initCarComponentLibrary( )
{
	static CCar::CFactory s_carFactory; // Ψһ�Ĺ���
}



/// ���Դ���
void testComponent()
{
	/// ��ʼ�������
	initCarComponentLibrary();

	/// ������ʲ���
	ICar* car = getComponentInstance<ICar>("BWM",CLSID);
	if(!car)
	{
		printf("create car failed !\n");
		return;
	}

	car->startEngine();

	if(!car->drive())
	{
		printf("drive failed !\n");
	}
   ///������� 
    car->destroy();

	
}
