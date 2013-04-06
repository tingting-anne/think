#ifndef _SESSION_H_
#define _SESSION_H_

namespace THINK {

class Session
{
public:
	Session(Socket* socket);
	
	virtual ~Session();
	
	void setIOComponent(IOComponent *ioc) {
        _iocomponent = ioc;
    }

    IOComponent *getIOComponent() {
        return _iocomponent;
    }

	
    /*
     * 写出数据
     */
    bool writeData();

    /*
     * 读入数据
     */
    bool readData();


	bool postPacket(Buffer *output, bool nonblock);

    /*
     * 当数据收到时的处理函数
     */
    bool handlePacket(Buffer *input);
private:
	bool _isServer;                         // 是服务器端
    IOComponent *_iocomponent;
    Socket *_socket;                        // Socket句柄
    CMsgQueue<Buffer* > _outQueue;
	CMsgQueue<Buffer* > _inQueue;
	CMsgQueue<Buffer* > _innerQueue;
	Buffer* _output;      // 输出的buffer
    Buffer* _input;       // 读入的buffer
};

}

#endif //_SESSION_H_
