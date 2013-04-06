#include "think.h"

namespace THINK {

IOComponent::IOComponent(EventLoop *loop, Socket *socket) 
: _loop(loop), _socket(socket)
{

	_socket->setIOComponent(this);
	_IOEvent = NULL;
	atomic_set(&_refcount, 0);
	
}

/*
 * Îö¹¹º¯Êý
 */
IOComponent::~IOComponent() {
	if (_socket) {
		_socket->close();
		delete _socket;
		_socket = NULL;
	}
}


}

