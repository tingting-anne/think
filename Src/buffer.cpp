#include "types.h"
#include "buffer.h"
#include <assert.h>
#include <string.h>

namespace THINK {
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

int Buffer::getSize()
{
	return end - head;
}

void Buffer::clear()
{
	data = tail = head;
}
// tail ָ�������ƣ����ڶ�
void Buffer::moveFree(int len)
{
	   assert(end - tail >= len);
         tail += len;
}

//data ָ�������ƣ�����д
void Buffer::moveData(int len)
{
	data += len;
	if (data  >= tail)
	{
		clear();
	}
}
//��ʼ�������
void Buffer::reserve(int len)
{
	data += len;
	tail += len;
}

void Buffer::ensureSpace(int len)
{
	expand(len);
}
/*
** ��չ���ݿռ�
*/
void Buffer::expand(int need)
{
	if (head == NULL) {     
            tail = data = head = (unsigned char*)malloc(need);
            end = head + need;
      } else if (getFreeLen() < need) { // �ռ䲻��

		unsigned char* newbuf = NULL;
           	int hl = getHeadLen();
		int dl = getDataLen();
		int sl = getSize();
		int bufsize = std::max(sl , need) * 2;
		newbuf =  (unsigned char*)malloc(bufsize);
		assert(newbuf);
		memcpy(newbuf , head, sl);
		free(head);
		head = newbuf;
		data = hl + head;
		tail = data + dl;
		end = head + bufsize;
	  
      }
}

}

