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
     * д������
     */
    bool writeData();

    /*
     * ��������
     */
    bool readData();


	bool postPacket(Buffer *output, bool nonblock);

    /*
     * �������յ�ʱ�Ĵ�����
     */
    bool handlePacket(Buffer *input);
private:
	bool _isServer;                         // �Ƿ�������
    IOComponent *_iocomponent;
    Socket *_socket;                        // Socket���
    CMsgQueue<Buffer* > _outQueue;
	CMsgQueue<Buffer* > _inQueue;
	CMsgQueue<Buffer* > _innerQueue;
	Buffer* _output;      // �����buffer
    Buffer* _input;       // �����buffer
};

}

#endif //_SESSION_H_
