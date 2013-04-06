#ifndef THINK_TCPCOMPONENT_H_
#define THINK_TCPCOMPONENT_H_

namespace THINK {

class TCPComponent : public IOComponent 
{
public:
	enum {
		connected = 0,
		unconnected,
		closed,
	};
  
    TCPComponent(EventLoop *loop, Socket *socket);

    ~TCPComponent();

    /*
     * 初始化
     *
     * @return 是否成功
     */
    bool init(bool isServer = false);

    /*
     * 关闭
     */
    void close();

   
    bool handleWrite();

    bool handleRead();

  
    Session *getSession() {
        return _session;
    }
	
    /*
     * 连接到socket
     */
    bool connect();

private:
    // TCP连接
    Session *_session;
    
};
}

#endif /*THINK_TCPCOMPONENT_H_*/


