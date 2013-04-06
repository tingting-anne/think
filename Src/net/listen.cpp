#include "think.h"

namespace THINK {

ListenComponent::ListenComponent(EventLoop* loop, Socket *socket) 
	:IOComponent(loop, socket) 
{
	
}

/*
 * 初始化, 开始监听
 */
bool ListenComponent::init(bool isServer) 
{
    nonblock(_socket->getfd());
    return _socket->listen();
}


bool ListenComponent::handleRead()
{
    Socket *socket = NULL;
    while ((socket = (_socket)->accept()) != NULL) {
       
        TCPComponent *component = new TCPComponent(_loop, socket);

        if (!component->init(true)) {
            delete component;
            return true;
        }

        // 加入到iocomponents中，及注册可读到socketevent中
        _loop->addComponent(component, true, false);
    }

    return true;
}

}


