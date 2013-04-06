#include "think.h"
#include "PrintLog.h"

namespace THINK {

EventLoop::EventLoop() : _socketEvent(new EPollEvent())
{
    _stop = false;
    _iocListChanged = false;
    _iocListCount = 0;
}

/*
 * ���캯��
 */
EventLoop::~EventLoop() 
{
    destroy();
}


bool EventLoop::start() {
    signal(SIGPIPE, SIG_IGN);
    _readWriteThread.start(this, _socketEvent);
    return true;
}

/*
 * ֹͣ��ͣ����д�̣߳������١�
 *
 * @return �Ƿ�ɹ�, true - �ɹ�, false - ʧ�ܡ�
 */
bool EventLoop::stop() {
    _stop = true;
    return true;
}

/*
 * �ȴ��߳���ȫ�˳���
 *
 * @return �Ƿ�ɹ�, true - �ɹ�, false - ʧ�ܡ�
 */
bool EventLoop::wait() {
    _readWriteThread.join();
    destroy();
    return true;
}

/*
 * socket event �ļ��, ��run��������
 */
void EventLoop::eventLoop(IOEvent *socketEvent) {
    IOPoll events[MAX_SOCKET_EVENTS];

    while (!_stop) {
        // ����Ƿ����¼�����
        int cnt = socketEvent->getEvents(1000, events, MAX_SOCKET_EVENTS);
        if (cnt < 0) {
            logError("events: %s(%d)\n", strerror(errno), errno);
        }

        for (int i = 0; i < cnt; i++) {
            IOComponent *ioc = (IOComponent*)(events[i]._ioc);
            if (ioc == NULL) {
                continue;
            }
            if (events[i]._error) { // ��������
                removeComponent(ioc);
                continue;
            }

            ioc->addRef();
            // ��д
            bool rc = true;
            if (events[i]._read) {
                rc = ioc->handleRead();
            }
            if (rc && events[i]._write) {
                rc = ioc->handleWrite();
            }
            ioc->subRef();

            if (!rc) {
                removeComponent(ioc);
            }
        }
    }
}

void EventLoop::run(CThread *thread, void *arg) 
{
     eventLoop((IOEvent*)arg);
    
}

void EventLoop::addComponent(IOComponent *ioc, bool readOn, bool writeOn) {
    assert(ioc != NULL);

    _iocMutex.Enter();
	_iocList.push_back(ioc);
    _iocListChanged = true;
    _iocListCount++;
    _iocMutex.Leave();

    // ����socketevent
    Socket *socket = ioc->getSocket();
    ioc->setIOEvent(_socketEvent);
    _socketEvent->addEvent(socket, readOn, writeOn);
   
}

/*
 * ɾ��iocomponet
 *
 * @param ioc: IO���
 */
void EventLoop::removeComponent(IOComponent *ioc) {
    assert(ioc != NULL);

    CGuard guard(_iocMutex);
    ioc->close();
	assert(std::find(_iocList.begin(), _iocList.end(), ioc) == _iocList.end());
	_iocList.remove(ioc);
    _iocListChanged = true;
    _iocListCount --;

}

/*
 * �ͷű���
 */
void EventLoop::destroy() {
    
    CGuard guard(_iocMutex);
    IOComponent *ioc = 0;
    // ɾ��iocList
    while (!_iocList.empty()) {
        ioc = _iocList.front();
		_iocList.pop_front();
		
		_iocListCount --;
		//assert(ioc->getRef() == 0);
        delete ioc;
		
    }
    _iocListCount = 0;
    delete _socketEvent;
}


}


