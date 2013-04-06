#ifndef _THINK_SERVER_H_
#define _THINK_SERVER_H_
//·þÎñ¶Ë
namespace THINK{
class TCPServer 
{
public:
	TCPServer();
	
	~TCPServer();

	bool start();

	bool stop();

	bool wait();
	
    bool listen(const char* addr, ushort port);

	virtual bool postBuffer(Buffer* buf, bool nonblock);

	virtual bool handleBuffer(Buffer* buf);
private:
	EventLoop  *_loop;
	Session * _session;
	
	
};
}
#endif //_THINK_SERVER_H_

