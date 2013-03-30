#include "buffer.h"

Buffer::Buffer()
{
	head = data = tail = end = NULL;
}

Buffer::~Buffer()
{
	if (head)
	{
		free(head);
		head = data = tail = end = NULL;
	}
}

char* Buffer::getData()
{
	return (char*)data;
}

int Buffer::getDataLen()
{
	return (tail - data);
}


char* Buffer::getFree()
{
	return (char*)tail;
}

int Buffer::getFreeLen()
{
	return (end - tail);
}


char* Buffer::getHead()
{
	return (char*)head;
}

int Buffer::getHeadLen()
{
	return (data - head);
}

void Buffer::clear()
{
	data = tail = head;
}
// tail 指针往后移，用于读
void Buffer::moveFree(int len)
{
	   assert(end - tail >= len);
         tail += len;
}

//data 指针往后移，用于写
void Buffer::moveData(int len)
{
	data += len;
	if (data  >= tail)
	{
		
	}
}

/*
** 拓展数据空间
*/
void Buffer::expand(int need)
{
	if (head == NULL) {           
            tail = data = head = (unsigned char*)malloc(need);
            end = head + need;
      } else if (getFreeLen() < need) { // 空间不够
           
           	
		  
      }
}

