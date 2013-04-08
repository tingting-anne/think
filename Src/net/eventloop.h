#ifndef _THINK_EVENT_LOOP_H_
#define _THINK_EVENT_LOOP_H_

#include "thread.h"

namespace THINK {

class EventLoop : public Runnable 
{

public:
	typedef std::list<IOComponent*, pool_allocator<IOComponent*> > IOCLIST;
	
    EventLoop();

    ~EventLoop();
	
    bool start();

    bool stop();

    /*
     * �ȴ��߳���ȫ�˳���
     *
     * @return �Ƿ�ɹ�, true - �ɹ�, false - ʧ�ܡ�
     */
    bool wait();

    /*
     * �̵߳����к�����ʵ��Runnable�ӿ��еĺ���
     *
     * @param arg: ����ʱ�������
     */
    void run(CThread *thread, void *arg);

    /*
     * ���뵽iocomponents��
     *
     * @param  ioc: IO���
     * @param  readOn: ��ʼ���Ѷ��¼���
     * @param  writeOn: ��ʼ����д�¼���
     */
    void addComponent(IOComponent *ioc, bool readOn, bool writeOn);

    /*
     * ��iocomponents��ɾ����
     *
     * @param ioc: IO���
     */
    void removeComponent(IOComponent *ioc);
    

private:
	/*
     * socket event �ļ��
     */
    void eventLoop(IOEvent *ioEvent);
    /*
     * �ͷű���
     */
    void destroy();

private:

    IOEvent*  _socketEvent;      // ��дsocket�¼�
    CThread _readWriteThread;    // ��д�����߳�
    bool _stop;                   // �Ƿ�ֹͣ
    bool _iocListChanged;       // IOComponent���ϱ��Ĺ�
    int _iocListCount;
	IOCLIST _iocList;
    CMutex _iocMutex;
	
};

}

#endif // _THINK_EVENT_LOOP_H_

