#ifndef _THINK_SOCK_EVENT_H_
#define _THINK_SOCK_EVENT_H_
#include "ioevent.h"

namespace THINK {

class EPollEvent : public IOEvent
{
public:

    EPollEvent();

    ~EPollEvent();

    virtual bool addEvent(Socket *socket, bool enableRead, bool enableWrite);

    virtual bool setEvent(Socket *socket, bool enableRead, bool enableWrite);

    virtual bool removeEvent(Socket *socket);

    virtual int getEvents(int timeout, IOPoll *events, int cnt);

private:
    int _efd;    // epollµÄfd
};

}


#endif //_THINK_SOCK_EVENT_H_