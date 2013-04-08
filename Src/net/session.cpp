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
	
}


bool Session::readData()
{
	
}


bool Session::postPacket(Buffer *output, bool nonblock)
{
	
}

bool Session::handlePacket(Buffer *input)
{
	
	
}

}
