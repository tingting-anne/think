#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "atomic.h"
/// \code
///  ===============================================
///               |
///          Buffer buffer
///               |------------+------------------+
///               |                             
///               |    
///               |                           
///               |     
///        buffer.reserve(len)         
///               |      
///               |           
///               |        
///               |                        
///               |------------+------------------+
///       buffer.ensureSpace(len)
///               |
///    ===============================================
/// \endcode

namespace THINK {

#define MAX_BUFFER_SIZE 2048
class Buffer 
{
public:
	Buffer();
	~Buffer();
	//引用计数
	int addRef();
	void release();

	char *getData();
	int getDataLen();

	char *getFree();
	int getFreeLen();
	
	char* getHead();
	int getHeadLen();

	int  getSize();
	void clear();
	
	void moveData(int len);
	void moveFree(int len);
	//adjust head room for protocol
	void reserve(int len);
	//
	void ensureSpace(int len);
private:	
	void expand(int need);
	
private:
	unsigned char	*head;			/* Head of buffer 				*/
	unsigned char	*data;			/* Data head pointer				*/
	unsigned char	*tail;			/* Tail pointer					*/
	unsigned char *end;			/* End pointer	*/
	atomic_t	_refcount;
};

} //end of namespace
#endif //_BUFFER_H_
