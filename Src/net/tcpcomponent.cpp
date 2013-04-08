#include "think.h"

namespace THINK {

TCPComponent::TCPComponent(EventLoop *loop, Socket *socket) 
:IOComponent(loop, socket)
{
	_session = new Session(socket);
    _session->setIOComponent(this);
	_isServer = false;
	_state = closed;
	
}
TCPComponent::~TCPComponent()
{
	if (_session) 
	{
        _session->setIOComponent(NULL);
        delete _session;
        _session = NULL;
    }
}

bool TCPComponent::init(bool isServer) {
  
    if (!isServer) {
        if (!connect()) {
            return false;
        }
    } else {
        _state = connected;
    }
    _isServer = isServer;

    return true;
}

/*
 * 连接到socket
 */
bool TCPComponent::connect() {
    if (_state == connected) 
	{
        return true;
    }
    nonblock(_socket->getfd());
	
    if (_socket->connect()) 
	{
        if (_IOEvent) {
            _IOEvent->addEvent(_socket, true, true);
        }
        _state = connected; 
    } 
	else 
	{
       
        _socket->close();
        _state = closed;
      
        return false;
        
    }
    return true;
}

/*
 * 关闭
 */
void TCPComponent::close() {
    if (_socket) {
        if (_IOEvent) {
            _IOEvent->removeEvent(_socket);
        }
       
        _socket->close();
        
        _state = closed;
    }
}


bool TCPComponent::handleWrite() {
    
    bool rc = true;
    if (_state == connected) {
        rc = _session->writeData();
    } 
    return rc;
}


bool TCPComponent::handleRead() {
   
    bool rc = false;
    if (_state == connected) {
        rc = _session->readData();
    }
    return rc;
}



}
