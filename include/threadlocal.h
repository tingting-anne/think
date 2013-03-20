/*
 ** describe the thread private value
 ** thread safe
 ** Author: yjhjstz(yjhjstz@163.com)
 ** 
 */
#ifndef _THINK_THREADLOCAL_H_
#define _THINK_THREADLOCAL_H_

#include <pthread.h>

namespace THINK{
class ThreadLocal {
public:
	ThreadLocal() {
	    pthread_key_create(&key, NULL);
	}
	virtual ~ThreadLocal(){
        pthread_key_delete(key);
    }
	void* get() 
    { 
          return (void*)pthread_getspecific(key); 
    }
	void set(void* data) 
    { 
         pthread_setspecific(key, (void *)data); 
    }

private:
	pthread_key_t key;
};

} // THINK

#endif //_THINK_THREADLOCAL_H_
