#include "think.h"
#include "PrintLog.h"


namespace THINK{

TCPServer::TCPServer(): _loop(new EventLoop) , _session(NULL)
{
	
}

TCPServer::~TCPServer() 
{
	delete _loop;
	_loop = NULL;
}

bool TCPServer::start()
{
	return _loop->start();
	
}

bool TCPServer::stop()
{
	return _loop->stop();
}

bool TCPServer::wait()
{
	return _loop->wait();
}

bool TCPServer::listen(const char* addr, ushort port)
{
	Socket *socket = new Socket();

	if (!socket->setAddr(addr, port)) {
		delete socket;
		return false;
	}

	// Listen
	ListenComponent *component = new ListenComponent(_loop, socket);

	if (!component->init(true)) {
	    delete component;
	    return false;
	}

	// 加入到iocomponents中，及注册可读到socketevent中
	_loop->addComponent(component, true, false);

	_session = component->getSession();
	_session->setHandlePacket(Session::DataProc(&TCPServer::handleBuffer, this));
	_session->setPostPacket(Session::DataProc(&TCPServer::postBuffer, this));
	// 返回
	return (_session != NULL);
}

bool TCPServer::postBuffer(Session* session, Buffer* buf)
{
	return _session->postPacket(buf, nonblock);
}

bool TCPServer::handleBuffer(Session* session, Buffer* buf)
{
	return _session->handlePacket(buf);
}


}

