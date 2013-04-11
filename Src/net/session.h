#ifndef _SESSION_H_
#define _SESSION_H_

namespace THINK {

class Session
{
public:
	typedef TFunction2<bool, Session*, Buffer*> DataProc;
	
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


	void setPostPacket(DataProc postdata){
		_postdata = postdata;
	}

    /*
     * 当数据收到时的处理函数
     */
    void setHandlePacket(DataProc handledata){
		_handledata = handledata;
	}

	bool postPacket(Buffer *output, bool nonblock);

	bool handlePacket(Buffer *input);

private:
	bool _isServer;                         // 是服务器端
	IOComponent *_iocomponent;
	Socket *_socket;                        // Socket句柄
	CMsgQueue<Buffer* > _outQueue;
	CMsgQueue<Buffer* > _inQueue;
	CMsgQueue<Buffer* > _innerQueue;
	Buffer _output;      // 输出的buffer
	Buffer _input;       // 读入的buffer
	DataProc _postdata;
	DataProc _handledata; 
	CMutex  _lock;
};

}

#endif //_SESSION_H_
