#ifndef _THINK_LISTEN_COMPONENT_H_
#define _THINK_LISTEN_COMPONENT_H_

namespace THINK {

class ListenComponent : public IOComponent
{
public :

	ListenComponent(EventLoop* loop , Socket* socket);
	
	~ListenComponent();
	
	bool init(bool isServer = false);

 
    bool handleRead();

 
    bool handleWrite() {
        return true;
    }
};

} //

#endif //_THINK_LISTEN_COMPONENT_H_
