#include "think.h"
#include "PrintLog.h"


namespace THINK {

Socket::Socket(bool server) : _ioc(0), _fd(-1), _isServer(server)
{
	
}

Socket::~Socket()
{
	close();
}

bool Socket::setAddr(const char* ip, ushort port)
{
	memset((void *)(&_address), 0, sizeof(_address));

    _address.sin_family = AF_INET;
    _address.sin_port = htons(port);
	if (ip == NULL){
		 _address.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else{
		_address.sin_addr.s_addr = inet_addr(ip);
	}
	
    return true;
}

bool Socket::setupFd(int fd, struct sockaddr *addr)
{
    close();
    _fd = fd;
    memcpy(&_address, addr, sizeof(_address));
    return true;
}

bool Socket::connect()
{
	if (!checkSock()) {
        return false;
    }
  //  logInfo("connect fd = %d, addr = %s\n", _fd, Ip2Str(ntohl(_address.sin_addr.s_addr)));
    return (0 == ::connect(_fd, (struct sockaddr *)&_address, sizeof(_address)));
}

bool Socket::close()
{
	if (_fd != -1){
		logInfo("close fd = %d\n", _fd);
		::close(_fd);
		_fd = -1;
	}
	return true;
}
bool Socket::shutdown()
{
	if (_fd != -1) {
        ::shutdown(_fd , SHUT_WR);
       	}
	return true;
}

int  Socket::getfd()
{
	return _fd;
}

IOComponent *Socket::getIOComponent() {
    return _ioc;
}


void Socket::setIOComponent(IOComponent *ioc) {
    _ioc = ioc;
}

/*
 * 写数据
 */
int Socket::write (const void *data, int len) {
    if (_fd == -1) {
        return -1;
    }

    int res;
    do {
        res = ::write(_fd, data, len);
        if (res > 0) {
        }
    } while (res < 0 && errno == EINTR);
    return res;
}

/*
 * 读数据
 */
int Socket::read (void *data, int len) {
    if (_fd == -1) {
        return -1;
    }

    int res;
    do {
        res = ::read(_fd, data, len);
        if (res > 0) {
           
        }
    } while (res < 0 && errno == EINTR);
    return res;
}

bool Socket::listen()
{
	int _backLog = 128;
	if (!_isServer){
		return false;
	}
	if (!checkSock()) {
        return false;
    }
	int value = 1;

	nonblock(_fd);
	
	setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR,
                         (const void *)(&value), sizeof(value));
	
	if (::bind(_fd, (struct sockaddr *)&_address,
               sizeof(_address)) < 0) {
        return false;
    }

    if (::listen(_fd, _backLog) < 0) {
        return false;
    }

    return true;
	
}

Socket *Socket::accept() 
{
   
    Socket *sock = NULL;
    if (!_isServer){
		return sock;
	}
    struct sockaddr_in addr;
    int len = sizeof(addr);

    int fd = ::accept(_fd, (struct sockaddr *)&addr, (socklen_t*)&len);

    if (fd >= 0) {
        sock = new Socket();
        sock->setupFd(fd, (struct sockaddr *)&addr);
		logInfo("new fd = %d\n", fd);
    } else {
        if (errno != EAGAIN) {
            logError("%s(%d)", strerror(errno), errno);
        }
    }

    return sock;
}

bool Socket::checkSock() 
{
    if (_fd == -1 && (_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        return false;
    }
    return true;
}

}


