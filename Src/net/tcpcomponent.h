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
     * ��ʼ��
     *
     * @return �Ƿ�ɹ�
     */
    bool init(bool isServer = false);

    /*
     * �ر�
     */
    void close();

   
    bool handleWrite();

    bool handleRead();

  
    Session *getSession() {
        return _session;
    }
	
    /*
     * ���ӵ�socket
     */
    bool connect();

private:
    // TCP����
    Session *_session;
    
};
}

#endif /*THINK_TCPCOMPONENT_H_*/


