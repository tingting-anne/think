#include "think.h"

namespace THINK {

ListenComponent::ListenComponent(EventLoop* loop, Socket *socket) 
	:IOComponent(loop, socket) 
{
	
}

/*
 * ��ʼ��, ��ʼ����
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

        // ���뵽iocomponents�У���ע��ɶ���socketevent��
        _loop->addComponent(component, true, false);
    }

    return true;
}

}


