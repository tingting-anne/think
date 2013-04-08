#ifndef _THINK_SERVER_H_
#define _THINK_SERVER_H_
//·þÎñ¶Ë
namespace THINK{
class TCPServer 
{
public:
	TCPServer();
	
	virtual  ~TCPServer();

	bool start();

	bool stop();

	bool wait();
	
    	bool listen(const char* addr, ushort port);

	virtual bool postBuffer(Session* session, Buffer* buf);

	virtual bool handleBuffer(Session* session, Buffer* buf);
private:
	EventLoop  *_loop;
	Session * _session;
	
	
};
}
#endif //_THINK_SERVER_H_

