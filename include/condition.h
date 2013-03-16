#ifndef _THREAD_CONDITION_H_
#define _THREAD_CONDITION_H_

#include "mutex.h"
#include "Guard.h"
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

namespace THINK{
class CThreadCond
{
public:
	CThreadCond()
	{
		pthread_cond_init(&cond, NULL);
		
	}
	CThreadCond(CMutex& mux):mutex(mux)
	{
		pthread_cond_init(&cond, NULL);
		
	}
	virtual ~CThreadCond()
	{
		int ret = pthread_cond_destroy(&cond);
		if( ret ) {

			printf( "CThreadCond::~CThreadCond: event destroy failure %s", strerror( ret ) );
			// seems we have threads waiting on us, lets wake them up
			pthread_cond_broadcast(&cond);

		}
	}

	// default argument causes thread to block indefinately
	bool wait(unsigned long time = 0)
	{
		
		
		int ret;
		if (time != 0){
			struct timeval tv;
			gettimeofday(&tv, 0);

			timespec ti;
			ti.tv_sec = tv.tv_sec + (time / 1000);
			ti.tv_nsec = (tv.tv_usec * 1000) + (time % 1000) * 1000000;

			ret = pthread_cond_timedwait(&(cond), (mutex.getMutex()), &ti);
		} 
		else //// сю╬ц╣х╢Щ
		{
			ret = pthread_cond_wait( &(cond), (mutex.getMutex()) );
		}



		if ( ret && ret != ETIMEDOUT )
			printf("CThreadCond::wait: wait error:%s",strerror(ret));


		return (ret == 0);
	}


	void signal()
	{
		int ret = pthread_cond_signal( &(cond) );
		if ( ret ) 
			printf("CThreadCond::signal: wake error: %s",strerror(ret));

	}
	void broadcast()
	{
		
		int ret = pthread_cond_broadcast(&(cond));
		if ( ret ) 
			printf("CThreadCond::broadcast: wake error: %s",strerror(ret));
			
	}

private:
	pthread_cond_t cond;
	CMutex mutex;

private:
	//disable copy and assign
	CThreadCond( const CThreadCond& );
	CThreadCond& operator=( const CThreadCond& );

};
}//end of namespace
#endif //_THREAD_CONDITION_H_
