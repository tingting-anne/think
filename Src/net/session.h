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
     * д������
     */
    bool writeData();

    /*
     * ��������
     */
    bool readData();


	void setPostPacket(DataProc postdata){
		_postdata = postdata;
	}

    /*
     * �������յ�ʱ�Ĵ�����
     */
    void setHandlePacket(DataProc handledata){
		_handledata = handledata;
	}

	bool postPacket(Buffer *output, bool nonblock);

	bool handlePacket(Buffer *input);

private:
	bool _isServer;                         // �Ƿ�������
	IOComponent *_iocomponent;
	Socket *_socket;                        // Socket���
	CMsgQueue<Buffer* > _outQueue;
	CMsgQueue<Buffer* > _inQueue;
	CMsgQueue<Buffer* > _innerQueue;
	Buffer _output;      // �����buffer
	Buffer _input;       // �����buffer
	DataProc _postdata;
	DataProc _handledata; 
	CMutex  _lock;
};

}

#endif //_SESSION_H_
