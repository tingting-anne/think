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
     * 等待线程完全退出。
     *
     * @return 是否成功, true - 成功, false - 失败。
     */
    bool wait();

    /*
     * 线程的运行函数，实现Runnable接口中的函数
     *
     * @param arg: 运行时传入参数
     */
    void run(CThread *thread, void *arg);

    /*
     * 加入到iocomponents中
     *
     * @param  ioc: IO组件
     * @param  readOn: 初始化把读事件打开
     * @param  writeOn: 初始化把写事件打开
     */
    void addComponent(IOComponent *ioc, bool readOn, bool writeOn);

    /*
     * 从iocomponents中删除掉
     *
     * @param ioc: IO组件
     */
    void removeComponent(IOComponent *ioc);
    

private:
	/*
     * socket event 的检测
     */
    void eventLoop(IOEvent *ioEvent);
    /*
     * 释放变量
     */
    void destroy();

private:

    IOEvent*  _socketEvent;      // 读写socket事件
    CThread _readWriteThread;    // 读写处理线程
    bool _stop;                   // 是否被停止
    bool _iocListChanged;       // IOComponent集合被改过
    int _iocListCount;
	IOCLIST _iocList;
    CMutex _iocMutex;
	
};

}

#endif // _THINK_EVENT_LOOP_H_

