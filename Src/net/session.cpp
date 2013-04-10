#include "think.h"

namespace THINK {

#define READ_WRITE_SIZE 2048

Session::Session(Socket* socket) : _socket(socket)
{
	_isServer = false;
	_iocomponent = NULL;
	
}

Session::~Session() 
{
    _socket = NULL;
    _iocomponent = NULL;
}

bool Session::writeData()
{
	int ret = false;
	Buffer* buffer = NULL;
	_innerQueue.splice(_outQueue);
		
	int innerSize = _innerQueue.size();
	do {
	 	
		ret = _innerQueue.pop(&buffer);

		if (buffer->getDataLen() == 0 || !ret) {
			break;
		}
		innerSize --;
		// write data
		ret = _socket->write(buffer->getData(), buffer->getDataLen());
		if (ret > 0) {
			buffer->moveData(ret);
		}
		
	} while (ret > 0 && innerSize>0 );
	
	int queueSize = _innerQueue.size() + (_output.getDataLen() > 0 ? 1 : 0);
	if ((queueSize == 0) && _iocomponent != NULL) {
	    _iocomponent->enableWrite(false);
	}
    	return true;
}


bool Session::readData()
{
	_input.ensureSpace(READ_WRITE_SIZE);
	int ret = _socket->read(_input.getFree(), _input.getFreeLen());
	if (ret > 0)
	{
		_handledata(this, &_input);
	}
	else if (ret == 0)
	{
		
	}
	return ret;
	
}


bool Session::postPacket(Buffer *output, bool nonblock)
{
	
}

bool Session::handlePacket(Buffer *input)
{
	
	
}

}
