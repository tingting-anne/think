
#include "PrintLog.h"
#include "CTime.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


////////////////////////////////////////////////////////////////////////////////

static int s_printLogLevel = 6;

// 记录上次输出最后一个字符是否是换行，还不完全可靠
static bool s_returned = true;

inline void print(char const* s)
{
	//if (s_print.empty())
	{
		// 这里不能使用 printf, 否则处理'%'会出错
		fputs(s, stdout);
	}
	
}


////////////////////////////////////////////////////////////////////////////////

namespace THINK {




void setPrintLogLevel(int level)
{
	s_printLogLevel = level;
}

////////////////////////////////////////////////////////////////////////////////

#define LOG_MSG(x, y) {\
	char buffer[8192]; \
	buffer[8191] = 0;	\
	if(s_returned) \
	{ \
		set_console_color(y);	\
		CTime t = CTime::getCurrentTime(); \
		snprintf(buffer, sizeof(buffer) - 1, "%02d:%02d:%02d|", t.hour, t.minute, t.second); \
		print(buffer);	\
		print(x); \
	} \
	va_list ap; \
	va_start(ap, fmt); \
	int n = vsnprintf(buffer, sizeof(buffer) - 1, fmt, ap); \
	va_end(ap);	\
	print(buffer); \
	s_returned = (n >= 8192 || n > 0 && buffer[n - 1] == '\n'); \
	if(s_returned) reset_console_color();\
	return int(n);	\
}


int logDebug(const char* fmt, ...)
{
	if(s_printLogLevel < 6)return 0;

	LOG_MSG("debug ", COLOR_DEBUG);
}

int logTrace(const char* fmt, ...)
{
	if(s_printLogLevel < 5)return 0;

	LOG_MSG("trace ", COLOR_TRACE);
}

int logInfo(const char* fmt, ...)
{
	if(s_printLogLevel < 4)return 0;

	LOG_MSG("info  ", COLOR_INFO);
}

int logWarn(const char* fmt, ...)
{
	if(s_printLogLevel < 3)return 0;

	LOG_MSG("warn  ", COLOR_WARN);
}

int logError(const char* fmt, ...)
{
	if(s_printLogLevel < 2)return 0;

	LOG_MSG("error ", COLOR_ERROR);
}

int logFatal(const char* fmt, ...)
{
	if(s_printLogLevel < 1)return 0;

	LOG_MSG("fatal ", COLOR_FATAL);
}




} // namespace THINK

