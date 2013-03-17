

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
/// 打印信息记录等等。
/// 打印信息分trace, debug, info, warn, error, fatal共6个级别，记录的形式可以是
/// 直接打印到标准输出，也可以记录到文件或者发送到远程日志服务器，目前只支持
/// 第一种方式。每行打印信息前自动加上了时间和打印类型的字符串，比如"12:54:12|info"
/// @{


/// 打印输出回调函数类型
/// 参数为要打印的字符串
typedef TFunction1<void, char const*> PrinterProc;

/// 设置打印的输出回调函数
/// \param [in] printer 输出回调函数, 为空时设置打印输出到标准输出设备
/// \return 成功返回0, 失败返回-1
int setLogPrinter(PrinterProc printer);

/// 设置打印的级别，高于该级别的打印不能输出
void setPrintLogLevel(int level);

/// 记录调试信息，级别6，不直接调用，用于实现debgf宏
/// \return 返回打印的字节数
int logDebug(const char* fmt, ...);

/// 记录跟踪信息，级别5，不直接调用，用于实现tracef宏
/// \return 返回打印的字节数
int logTrace(const char* fmt, ...);

/// 记录调试信息，级别4，不直接调用，用于实现infof宏
/// \return 返回打印的字节数
int logInfo(const char* fmt, ...);

/// 记录警告信息，级别3，不直接调用，用于实现warnf宏
/// \return 返回打印的字节数
int logWarn(const char* fmt, ...);

/// 记录错误信息，级别2，不直接调用，用于实现errorf宏
/// \return 返回打印的字节数
int logError(const char* fmt, ...);

/// 记录致命错误信息，级别1，不直接调用，用于实现fatalf宏
/// \return 返回打印的字节数
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


