

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "CTime.h"
#define LINUX

#ifdef WIN32
	#include <Windows.h>
#elif defined(LINUX)
	#include <sys/time.h>
	#include <sys/times.h>
	#include <sys/select.h>
    #include <linux/unistd.h>
#ifdef CONFIG_CKCORE
	#define sysconf
	#define _SC_CLK_TCK 100
#else
//	_syscall1(clock_t, times, struct tms *, buf); // 直接调用系统函数times,避免tick值跳变
#endif
#else
	#error "Unknown Platform"
#endif

namespace THINK{
std::string CTime::m_format = "yyyy-MM-dd HH:mm:ss";


int CTime::m_dateFormat = ymd;
char CTime::m_dateSeparator = '-';
bool CTime::m_12hour = false;
static uint64 m_tickoffs = 0;	//tick计数校正

const CTime CTime::minTime(2000, 1, 1, 0, 0, 0);
const CTime CTime::maxTime(2038, 1, 1, 0, 0, 0);


CTime::CTime()
{
}

CTime::CTime(uint64 time)
{
	breakTime(time);
}

CTime::CTime( int vyear, int vmonth, int vday, int vhour, int vmin, int vsec)
{
	struct tm t;

	year = vyear;
	t.tm_year = year - 1900;
	month = vmonth;
	t.tm_mon = vmonth - 1;
	day = t.tm_wday = vday;
	hour = t.tm_hour = vhour;
	minute = t.tm_min = vmin;
	second = t.tm_sec = vsec;

	breakTime(makeTime()); // 值校验，规范化，生成星期
}

CTime CTime::getCurrentTime()
{
#ifdef WIN32
	SYSTEMTIME time;

	GetLocalTime(&time);
	return CTime(time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

#elif defined(LINUX)
	CTime t;
	struct timeval tv;

	gettimeofday(&tv, 0);

	t.breakTime(tv.tv_sec);

	return t;

#elif defined(__TCS__)
	ulong date, time, ticks;

	tm_get(&date, &time, &ticks);
	return CTime((date >> 16), ((date >> 8) & 0xff), (date & 0xff),
		(time >> 16), ((time >> 8) & 0xff), (time & 0xff));

#endif
}

void CTime::setCurrentTime(const CTime& time)
{
#ifdef WIN32
	SYSTEMTIME t;

	t.wYear = time.year;
	t.wMonth = time.month;
	t.wDay = time.day;
	t.wHour = time.hour;
	t.wMinute = time.minute;
	t.wSecond = time.second;
	SetLocalTime(&t);

#elif defined(LINUX)
	struct timeval tv;

	tv.tv_sec = time.makeTime();
	tv.tv_usec = 0;

	settimeofday(&tv, 0);
	
	// 同步到rtc
	system("hwclock -w");

#elif defined(__TCS__)
	tm_set((time.year << 16) + (time.month << 8) + time.day,
		(time.hour << 16) + (time.minute << 8) + time.second,
		0);

#endif
}

uint64 CTime::getCurrentMilliSecond()
{
#ifdef WIN32
	LARGE_INTEGER c;
	QueryPerformanceCounter(&c);
	return (int64)((((double)c.QuadPart / ddFreq) - ddBaseTime) / 1000);

#elif defined(LINUX)
	uint64 tick = (uint64)times(NULL); // 产生从0开始的tick计数，大约可以坚持20个月不溢出
	if(m_tickoffs == 0)
	{
		m_tickoffs = 0 - tick;
	}

	return (tick + m_tickoffs) * (1000 / sysconf(_SC_CLK_TCK));

#elif defined(__TCS__)
	ulong hi, lo;

	tm_getticks(&hi, &lo);
	return (((uint64)hi << 32) + lo)* (1000 / KC_TICKS2SEC);

#else
#error "Unknown Platform"
#endif
}

uint64 CTime::getCurrentMicroSecond()
{
#ifdef WIN32
	LARGE_INTEGER c;
	QueryPerformanceCounter(&c);
	return (int64)(((double)c.QuadPart / ddFreq) - ddBaseTime);

#elif defined(LINUX)
	struct timeval tv;
	struct timezone	tz;
	gettimeofday(&tv, &tz);
	return ((int64)tv.tv_sec * 1000 * 1000 + tv.tv_usec);
	
#elif defined(__TCS__)
	return getCurrentMicroSecond() * 1000;

#else
#error "Unknown Platform"
#endif
}

void CTime::sleep(int ms)
{
#ifdef WIN32
	Sleep(ms);

#elif defined(LINUX)
#if 0
	struct timespec t;

	t.tv_sec = ms / 1000;
	t.tv_nsec = ((ms % 1000) * 1000000); // 0 to 999 999 999
	while(nanosleep(&t, &t) != 0);
#else // uclinux下select更准确，且延时时间越长越准确
	struct timeval t;

	t.tv_sec = ms / 1000;
	t.tv_usec = ((ms % 1000) * 1000);
	while(select(0, NULL, NULL, NULL, &t) != 0);
#endif
	
#elif defined(__TCS__)
	struct timeval t;

	t.tv_sec = ms / 1000;
	t.tv_usec = ((ms % 1000) * 1000);
	while(select(0, NULL, NULL, NULL, &t) != 0);

#else
#error "Unknown Platform"
#endif
}

void CTime::setFormat(const std::string format)
{
	m_format = format;

	// 设置日期分隔符
	if(m_format.find('.') != m_format.npos)
	{
		m_dateSeparator = '.';
	}
	else if(m_format.find('/') != m_format.npos)
	{
		m_dateSeparator = '/';
	}
	else if(m_format.find('-') != m_format.npos)
	{
		m_dateSeparator = '-';
	}
	else
	{
		assert(0);
	}
	
	// 设置小时格式
	m_12hour = (m_format.find('h') != m_format.npos);

	// 设置日期格式
	uint pos1 = m_format.find('y');
	uint pos2 = m_format.find('M');
	uint pos3 = m_format.find('d');
	if(pos1 < pos2 && pos2 < pos3)
	{
		m_dateFormat = ymd;
	}
	else if(pos2 < pos3 && pos3 < pos1)
	{
		m_dateFormat = mdy;
	}
	else if(pos3 < pos2 && pos2 < pos1)
	{
		m_dateFormat = dmy;
	}
	else
	{
		assert(0);
	}
}

const std::string CTime::getFormat()
{
	return m_format;
}

int CTime::getDateFormat()
{
	return m_dateFormat;
}

bool CTime::get12Hour()
{
	return m_12hour;
}

char CTime::getSpliter()
{
	return m_dateSeparator;
}

uint64 CTime::makeTime() const
{
	time_t		tt;
	struct tm	t;

	t.tm_sec	= second;
	t.tm_min	= minute;
	t.tm_hour	= hour;
	t.tm_mday	= day;
	t.tm_mon	= month - 1;
	t.tm_year	= year - 1900;
	t.tm_isdst = 0;

	tt = mktime(&t);

	//assert(tt > 0);
	if (tt < 0)
	{
		tt = 0;
	}
	
	return (uint64)tt;
}

void CTime::breakTime(uint64 time)
{
	struct tm t;
	time_t tt = (time_t)time; // linux下可能是32位，会溢出
	if(time != (uint64)tt)
	{
		printf("CTime::breakTime overflowed!\n");
	}

	//need protect ???
#if defined(WIN32) || defined(__TCS__)
	t = *localtime(&tt);	
#else
	localtime_r(&tt, &t);	
#endif

	year =  t.tm_year + 1900;
	month = t.tm_mon + 1;
	wday = t.tm_wday;
	day = t.tm_mday;
	hour = t.tm_hour;
	minute = t.tm_min;
	second = t.tm_sec;
}



CTime CTime::operator +( int64 seconds ) const
{
	CTime time;
	time.breakTime(makeTime() + seconds);

	return time;
}

CTime CTime::operator -( int64 seconds ) const
{
	CTime time;
	time.breakTime(makeTime() - seconds);

	return time;
}

int64 CTime::operator -(const CTime& time ) const
{
	return ((int64)makeTime() - (int64)time.makeTime());
}

CTime& CTime::operator += (int64 seconds)
{
	breakTime(uint64((int64)makeTime() + seconds));

	return *this;
}

CTime& CTime::operator -= (int64 seconds)
{
	breakTime(uint64((int64)makeTime() - seconds));

	return *this;
}

bool CTime::operator == (const CTime& time) const
{
	return (makeTime() == time.makeTime());
}

bool CTime::operator != (const CTime& time) const
{
	return (makeTime() != time.makeTime());
}

bool CTime::operator > (const CTime& time) const
{
	return (makeTime() > time.makeTime());
}

bool CTime::operator >= (const CTime& time) const
{
	return (makeTime() >= time.makeTime());
}

bool CTime::operator < (const CTime& time) const
{
	return (makeTime() < time.makeTime());
}

bool CTime::operator <= (const CTime& time) const
{
	return (makeTime() <= time.makeTime());
}

void CTime::format(char* buf, const char *format) const
{
	char temp[8];
	char tempYear[8];
	char tempMonth[8];
	char tempDay[8];
	const char* str[3];
	int istr = 0;

	assert(buf);
	buf[0] = '\0';


	// 12小时换算
	int h = this->hour;
	if(m_12hour)
	{
		if(h > 12)
		{
			h -= 12;
		}
		else if(h == 0)
		{
			h = 12;
		}
	}

	// 日期字符串格式化
	int ny = 0, nm = 0, nd = 0;
	const char *p = format;
	while(*p)
	{
		if(*p == 'y')
		{
			ny++;
		}
		else if(*p == 'M')
		{
			nm++;
		}
		else if(*p == 'd')
		{
			nd++;
		}
		p++;
	}
	if(ny > 2)
	{
		sprintf(tempYear, "%04d", year);
	}
	else if(ny > 0)
	{
		sprintf(tempYear, "%02d", year % 100);
	}
	else
	{
		tempYear[0] = '\0';
	}

	if(nm > 0)
	{
		sprintf(tempMonth, (nm == 1) ? "%d" : "%02d", month);
	}
	else
	{
		tempMonth[0] = '\0';
	}

	if(nd > 0)
	{
		sprintf(tempDay, (nd == 1) ? "%d" : "%02d", day);
	}
	else
	{
		tempDay[0] = '\0';
	}

	// 日期字符串排序
	if(m_dateFormat == ymd)
	{
		str[0] = tempYear;
		str[1] = tempMonth;
		str[2] = tempDay;
	}
	else if(m_dateFormat == mdy)
	{
		str[0] = tempMonth;
		str[1] = tempDay;
		str[2] = tempYear;
	}
	else if(m_dateFormat == dmy)
	{
		str[0] = tempDay;
		str[1] = tempMonth;
		str[2] = tempYear;
	}

	// 去掉无效的日期字符串
	if(str[0][0] == '\0')
	{
		str[0] = str[1];
		str[1] = str[2];
	}
	else if(str[1][0] == '\0')
	{
		str[1] = str[2];
	}
	

	// 扫描格式字符串，逐步格式化
	uint size = strlen(format);
	for(uint i = 0; i < size; i++)
	{
		uint n = i;
		switch(format[i])
		{
//		case '-':
//		case '.':
//		case '/':
//			strncat(buf, &m_dateSeparator, 1);
//			break;

		case 'y':
		case 'M':
		case 'd':
			while(n < size && format[++n] == format[i]);
			strcat(buf, str[istr++]);
			i = n - 1;
			break;

		case 'H':
		case 'h':
			while(n < size && (format[n] == 'h' || format[n] == 'H'))
				++n;
			sprintf(temp, (n == i + 1) ? "%d" : "%02d", h);
			strcat(buf, temp);
			i = n - 1;
			break;

		case 'm':
			while(n < size && format[++n] == 'm');
			sprintf(temp, (n == i + 1) ? "%d" : "%02d", minute);
			strcat(buf, temp);
			i = n - 1;
			break;

		case 's':
			while(n < size && format[++n] == 's');
			sprintf(temp, (n == i + 1) ? "%d" : "%02d", second);
			strcat(buf, temp);
			i = n - 1;
			break;

		case 't':
			if(m_12hour)
			{
				while(n < size && format[++n] == 't');
				strcat(buf,hour/12?"PM":"AM");
				i = n - 1;
			}
			else
			{
				n = strlen(buf);
				while(n > 0 && buf[n - 1] == ' ')// 删除多余的空格
				{
					buf[n - 1] = '\0';
					n--;
				}
			}
			break;

		default:
			strncat(buf, format + i, 1);
			break;
		}
	}
}

} // end of namespace

