#include "think.h"

namespace THINK {

EPollEvent::EPollEvent() 
{
	_efd = epoll_create(MAX_SOCKET_EVENTS);
}

EPollEvent::~EPollEvent()
{
	close(_efd);	
}

bool EPollEvent::addEvent(Socket *socket, bool enableRead, bool enableWrite) 
{

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.ptr = socket->getIOComponent();
    // 设置要处理的事件类型
    ev.events = 0;

    if (enableRead) {
        ev.events |= EPOLLIN;
    }
    if (enableWrite) {
        ev.events |= EPOLLOUT;
    }

    bool rc = (epoll_ctl(_efd, EPOLL_CTL_ADD, socket->getfd(), &ev) == 0);
    return rc;
}

bool EPollEvent::setEvent(Socket *socket, bool enableRead, bool enableWrite) 
{

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.ptr = socket->getIOComponent();
    // 设置要处理的事件类型
    ev.events = 0;

    if (enableRead) {
        ev.events |= EPOLLIN;
    }
    if (enableWrite) {
        ev.events |= EPOLLOUT;
    }

    bool rc = (epoll_ctl(_efd, EPOLL_CTL_MOD, socket->getfd(), &ev) == 0);
    return rc;
}


bool EPollEvent::removeEvent(Socket *socket) {

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.ptr = socket->getIOComponent();
    // 设置要处理的事件类型
    ev.events = 0;

    bool rc = (epoll_ctl(_efd, EPOLL_CTL_DEL, socket->getfd(), &ev) == 0);
    return rc;
}


int EPollEvent::getEvents(int timeout, IOPoll *ioevents, int cnt) {

    struct epoll_event events[MAX_SOCKET_EVENTS];

    if (cnt > MAX_SOCKET_EVENTS) {
        cnt = MAX_SOCKET_EVENTS;
    }

    int res = epoll_wait(_efd, events, cnt , timeout);

    // 初始化
    if (res > 0) {
        memset(ioevents, 0, sizeof(IOPoll) * res);
    }

    // 把events的事件转化成IOPoll的事件
    for (int i = 0; i < res; i++) {
        ioevents[i]._ioc = events[i].data.ptr;
        if (events[i].events & (EPOLLERR | EPOLLHUP)) {
            ioevents[i]._error = true;
        }
        if ((events[i].events & EPOLLIN) != 0) {
            ioevents[i]._read = true;
        }
        if ((events[i].events & EPOLLOUT) != 0) {
            ioevents[i]._write = true;
        }
    }

    return res;
}

}

