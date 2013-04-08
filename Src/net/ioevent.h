#ifndef THINK_SOCKETEVENT_H_
#define THINK_SOCKETEVENT_H_

namespace THINK {

#define MAX_SOCKET_EVENTS 128

struct IOPoll {

public:
    bool _read;  // ������
    bool _write;  // д����
    bool _error;  // ������
    void *_ioc;  // �ش�����
};

class IOEvent {

public:
    /*
     * ���캯��
     */
    IOEvent();
    /*
     * ��������
     */
    virtual ~IOEvent();
    /*
     * ����Socket���¼���
     *
     * @param socket ���ӵ�socket
     * @param enableRead: �����Ƿ�ɶ�
     * @param enableWrite: �����Ƿ��д
     * @return  �����Ƿ�ɹ�, true �C �ɹ�, false �C ʧ��
     */
    virtual bool addEvent(Socket *socket, bool enableRead, bool enableWrite) = 0;

    /*
     * ����ɾ��Socket���¼���
     *
     * @param socket ���ӵ�socket
     * @param enableRead: �����Ƿ�ɶ�
     * @param enableWrite: �����Ƿ��д
     * @return  �����Ƿ�ɹ�, true �C �ɹ�, false �C ʧ��
     */
    virtual bool setEvent(Socket *socket, bool enableRead, bool enableWrite) = 0;

    /*
        * ɾ��Socket���¼���
        *
        * @param socket ��ɾ��socket
        * @return  �����Ƿ�ɹ�, true �C �ɹ�, false �C ʧ��
        */
    virtual bool removeEvent(Socket *socket) = 0;

    /*
     * �õ���д�¼���
     *
    * @param timeout  ��ʱʱ��(��λ:ms)
    * @param events  �¼�����
    * @param cnt   events�������С
    * @return �¼���, 0Ϊ��ʱ
     */
    virtual int getEvents(int timeout, IOPoll *events, int cnt) = 0;
};
}

#endif /**/

