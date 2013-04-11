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

		if ( !ret || buffer->getDataLen() == 0) {
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
		handlePacket(&_input);
	}
	else if (ret == 0)
	{
		//_iocomponent->close();
	}
	return ret;
	
}


bool Session::postPacket(Buffer *output, bool nonblock)
{
	
	_lock.Enter();
	_outQueue.push(output);
	if (_iocomponent != NULL && _outQueue.size() == 1U) {
	_iocomponent->enableWrite(true);
	}
	_lock.Leave();
	return true;
}

bool Session::handlePacket(Buffer *input)
{
	return _handledata(this, input);
	
}

}
