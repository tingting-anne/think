

#ifndef __THINK_PRINT_LOG_H__
#define __THINK_PRINT_LOG_H__

#include <stdio.h>
#include "inttype.h"
#include "Function.h"

enum {
	COLOR_FATAL = 35,
	COLOR_ERROR = 31,
	COLOR_WARN = 33,
	COLOR_INFO = 32,
	COLOR_TRACE = 37,
	COLOR_DEBUG = 36
};

inline void set_console_color(int c)
{
	fprintf(stdout, "\033[%d;40m", c);
}

inline void reset_console_color()
{
	fprintf(stdout, "\033[0m");
}

namespace THINK{


/// \defgroup PrintLog PrintLog
/// ��ӡ��Ϣ��¼�ȵȡ�
/// ��ӡ��Ϣ��trace, debug, info, warn, error, fatal��6�����𣬼�¼����ʽ������
/// ֱ�Ӵ�ӡ����׼�����Ҳ���Լ�¼���ļ����߷��͵�Զ����־��������Ŀǰֻ֧��
/// ��һ�ַ�ʽ��ÿ�д�ӡ��Ϣǰ�Զ�������ʱ��ʹ�ӡ���͵��ַ���������"12:54:12|info"
/// @{


/// ��ӡ����ص���������
/// ����ΪҪ��ӡ���ַ���
typedef TFunction1<void, char const*> PrinterProc;

/// ���ô�ӡ������ص�����
/// \param [in] printer ����ص�����, Ϊ��ʱ���ô�ӡ�������׼����豸
/// \return �ɹ�����0, ʧ�ܷ���-1
int setLogPrinter(PrinterProc printer);

/// ���ô�ӡ�ļ��𣬸��ڸü���Ĵ�ӡ�������
void setPrintLogLevel(int level);

/// ��¼������Ϣ������6����ֱ�ӵ��ã�����ʵ��debgf��
/// \return ���ش�ӡ���ֽ���
int logDebug(const char* fmt, ...);

/// ��¼������Ϣ������5����ֱ�ӵ��ã�����ʵ��tracef��
/// \return ���ش�ӡ���ֽ���
int logTrace(const char* fmt, ...);

/// ��¼������Ϣ������4����ֱ�ӵ��ã�����ʵ��infof��
/// \return ���ش�ӡ���ֽ���
int logInfo(const char* fmt, ...);

/// ��¼������Ϣ������3����ֱ�ӵ��ã�����ʵ��warnf��
/// \return ���ش�ӡ���ֽ���
int logWarn(const char* fmt, ...);

/// ��¼������Ϣ������2����ֱ�ӵ��ã�����ʵ��errorf��
/// \return ���ش�ӡ���ֽ���
int logError(const char* fmt, ...);

/// ��¼����������Ϣ������1����ֱ�ӵ��ã�����ʵ��fatalf��
/// \return ���ش�ӡ���ֽ���
int logFatal(const char* fmt, ...);



//////////////////////////////////////////////////////////////////////////
// print message, controlled by messsage level

#ifdef __GNUC__ // perform complete xxxxf macro replacement
#	define debugf(format, ...) logDebug(format, ## __VA_ARGS__)
#	define tracef(format, ...) logTrace(format, ## __VA_ARGS__)
#	define infof(format, ...) logInfo(format, ## __VA_ARGS__)
#	define warnf(format, ...) logWarn(format, ## __VA_ARGS__)
#	define errorf(format, ...) logError(format, ## __VA_ARGS__)
#	define fatalf(format, ...) logFatal(format, ## __VA_ARGS__)
#else
#	define debugf logDebug
#	define tracef logTrace
#	define infof logInfo
#	define warnf logWarn
#	define errorf logError
#	define fatalf logFatal
#endif

#define tracepoint()  logDebug("tracepoint: %s, %d.\n",__FILE__,__LINE__)


/// @} end of group


} // namespace THINK

#endif //__THINK_PRINT_LOG_H__


