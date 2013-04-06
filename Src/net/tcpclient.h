#ifndef _THINK_CLIENT_H_
#define _THINK_CLIENT_H_
namespace THINK{
class TCPClient 
{
public:
	TCPClient();
	
	~TCPClient();

	bool start();

	bool stop();
	
    bool connect(const char* addr, ushort port);

    bool disconnect();

	virtual bool postBuffer(Buffer* buf, bool nonblock);

	virtual bool handleBuffer(Buffer* buf);
private:
	EventLoop  *_loop;
	Session * _session;
	
	
};
}
#endif //_THINK_CLIENT_H_
