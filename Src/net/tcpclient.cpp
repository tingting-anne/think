#include "think.h"
#include "PrintLog.h"


namespace THINK{
TCPClient::TCPClient(): _loop(new EventLoop) , _session(NULL)
{
	
}

TCPClient::~TCPClient() 
{
	delete _loop;
	_loop = NULL;
}

bool TCPClient::start()
{
	_loop->start();
	return _loop->wait();
}

bool TCPClient::stop()
{
	return _loop->stop();
}

bool TCPClient::connect(const char* addr, ushort port)
{
		Socket *socket = new Socket();

        if (!socket->setAddr(addr, port)) {
            delete socket;
            return false;
        }

        // TCPComponent
        TCPComponent *component = new TCPComponent(_loop, socket);
       
        if (!component->init()) {
            delete component;
            logInfo("初始化失败TCPComponent: %s:%d", addr, port);
            return false;
        }

        // 加入到iocomponents中，及注册可写到socketevent中
        _loop->addComponent(component, true, true);
        component->addRef();

        _session = component->getSession();

		return (_session != NULL);
}


bool TCPClient::disconnect() 
{
    IOComponent *ioc = NULL;
    if (_session == NULL || (ioc = _session->getIOComponent()) == NULL) {
        return false;
    }

    ioc->subRef();
    if (ioc) {
        ioc->getSocket()->shutdown();
    }
    return true;
}

bool TCPClient::postBuffer(Buffer* buf, bool nonblock)
{
	return _session->postPacket(buf, nonblock);
}

bool TCPClient::handleBuffer(Buffer* buf)
{
	return _session->handlePacket(buf);
}


}
