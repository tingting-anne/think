#ifndef _THINK_SOCK_H_
#define _THINK_SOCK_H_

namespace THINK {

class IOComponent;
//not thread safe
class Socket {
	
public:
		
		Socket(bool server = false);
	
		~Socket();

		bool setAddr(const char* ip, ushort port);

		bool setupFd(int fd, struct sockaddr *addr);
		
		bool connect();

		bool close();

		bool shutdown();

		int  getfd();

		IOComponent *getIOComponent();

    	void setIOComponent(IOComponent *ioc);

		int write(const void *data, int len);

   		int read(void *data, int len);
		
		//服务端接口
		bool listen();

		Socket *accept();
private:
		bool checkSock();
private:
		IOComponent *_ioc;
		int _fd;
		bool _isServer;
		struct sockaddr_in  _address; // 地址
};

}

#endif //
