#ifndef _BUFFER_H_
#define _BUFFER_H_

#define MAX_BUFFER_SIZE 2048
class Buffer 
{
public:
	Buffer();
	~Buffer();

	char *getData();
	int getDataLen();

	char *getFree();
	int getFreeLen();
	
	char* getHead();
	int getHeadLen();

	void clear();
	
	void moveData(int len);
	void moveFree(int len);

	
private:	
	void expand(int need);
	
private:
	unsigned char	*head;			/* Head of buffer 				*/
	unsigned char	*data;			/* Data head pointer				*/
	unsigned char	*tail;			/* Tail pointer					*/
	unsigned char *end;			/* End pointer	*/
	//atomic_t	users;
};

#endif //_BUFFER_H_
