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
     * 初始化
     *
     * @return 是否成功
     */
    virtual bool init(bool isServer = false) = 0;

    /*
     * 关闭
     */
    virtual void close() {}
  
    virtual bool handleWrite() = 0;

    virtual bool handleRead() = 0;

    /*
     * 得到socket句柄
     *
     * @return Socket
     */
    Socket *getSocket() {
        return _socket;
    }

    /*
     * 设置SocketEvent
     */
    void setIOEvent(IOEvent *event) {
        _IOEvent = event;
    }

    /*
     * 设置能读写
     *
     * @param writeOn 写是否打开
     */
    void enableWrite(bool writeOn) {
        if (_IOEvent) {
            _IOEvent->setEvent(_socket, true, writeOn);
        }
    }

    /*
     * 增加引用计数
     */
    int addRef() {
        return atomic_add_return(1, &_refcount);
    }

    /*
     * 减少引用计数
     */
    void subRef() {
        atomic_dec(&_refcount);
    }

    /*
     * 取出引用计数
     */
    int getRef() {
        return atomic_read(&_refcount);
    }
	
    /*
     * 得到连接状态
     */
    int getState() {
        return _state;
    }
	
protected:
    EventLoop *_loop;
    Socket *_socket;    // 一个Socket的文件句柄
    IOEvent *_IOEvent;
    int _state;         // 连接状态
    atomic_t _refcount; // 引用计数
    bool _isServer;     // 是否为服务器端
};

}
#endif //
