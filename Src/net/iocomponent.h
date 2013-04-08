#ifndef _THINK_IO_COMPOENT_H_
#define _THINK_IO_COMPOENT_H_


namespace THINK {

class EventLoop;
class IOComponent 
{
public:
   
    IOComponent(EventLoop *loop, Socket *socket);
  
    virtual ~IOComponent();

    /*
     * ��ʼ��
     *
     * @return �Ƿ�ɹ�
     */
    virtual bool init(bool isServer = false) = 0;

    /*
     * �ر�
     */
    virtual void close() {}
  
    virtual bool handleWrite() = 0;

    virtual bool handleRead() = 0;

    /*
     * �õ�socket���
     *
     * @return Socket
     */
    Socket *getSocket() {
        return _socket;
    }

    /*
     * ����SocketEvent
     */
    void setIOEvent(IOEvent *event) {
        _IOEvent = event;
    }

    /*
     * �����ܶ�д
     *
     * @param writeOn д�Ƿ��
     */
    void enableWrite(bool writeOn) {
        if (_IOEvent) {
            _IOEvent->setEvent(_socket, true, writeOn);
        }
    }

    /*
     * �������ü���
     */
    int addRef() {
        return atomic_add_return(1, &_refcount);
    }

    /*
     * �������ü���
     */
    void subRef() {
        atomic_dec(&_refcount);
    }

    /*
     * ȡ�����ü���
     */
    int getRef() {
        return atomic_read(&_refcount);
    }
	
    /*
     * �õ�����״̬
     */
    int getState() {
        return _state;
    }
	
protected:
    EventLoop *_loop;
    Socket *_socket;    // һ��Socket���ļ����
    IOEvent *_IOEvent;
    int _state;         // ����״̬
    atomic_t _refcount; // ���ü���
    bool _isServer;     // �Ƿ�Ϊ��������
};

}
#endif //
