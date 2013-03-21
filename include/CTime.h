#ifndef __TIME_WRAPPER_H__
#define __TIME_WRAPPER_H__

#include "types.h"
#include <string>
namespace THINK{
/// 系统时间结构
typedef struct SYSTEM_TIME{
	int  year;///< 年。   
	int  month;///< 月，January = 1, February = 2, and so on.   
	int  day;///< 日。   
	int  wday;///< 星期，Sunday = 0, Monday = 1, and so on   
	int  hour;///< 时。   
	int  minute;///< 分。   
	int  second;///< 秒。   
	int  isdst;///< 夏令时标识。   
}SYSTEM_TIME;

/// \class CTime
/// \brief 时间类，实现了本地时间存取，运算，格式控制与打印等接口
class CTime : public SYSTEM_TIME
{
public:
	enum DataFormat
	{
		ymd,
		mdy,
		dmy
	};

	/// 缺省构造函数
	CTime( );

	/// 相对时间构造函数
	CTime(uint64 time);

	/// 普通时间构造函数
	CTime( int vyear, int vmonth, int vday, int vhour, int vmin, int vsec);
	
	CTime(const SYSTEM_TIME& stm)
	{
		year = stm.year;
		month = stm.month;
		day = stm.day;
		wday = stm.wday;
		hour = stm.hour;
		minute = stm.minute;
		second = stm.second;
		isdst = stm.isdst;
	}
	
	/// 得到相对时间，相对时间指从1900-1-1 00:00:00到某个时刻经过的秒数
	/// \return 相对时间
	uint64 makeTime() const;

	/// 分解相对时间
	/// \param time 相对时间
	void breakTime(uint64 time);

	/// 时间调节
	/// \param seconds 调节的秒数
	/// \return 调节后新的时间对象
	CTime operator +( int64 seconds ) const;

	/// 时间调节
	/// \param seconds 调节的秒数
	/// \return 调节后新的时间对象
	CTime operator -( int64 seconds ) const;

	/// 时间差运算
	/// \param time 相比较的时间
	/// \return 比较的结果，为(*this - time)得到的秒数
	int64 operator -( const CTime& time ) const;

	/// 时间调节
	/// \param seconds 调节的秒数
	/// \return 对象本身
	CTime& operator +=( int64 seconds );

	/// 时间调节
	/// \param seconds 调节的秒数
	/// \return 对象本身
	CTime& operator -=( int64 seconds );

	/// 时间比较
	/// \param time 相比较的时间
	/// \return 相等返回true，否则返回false
	bool operator == (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return 不等返回true，否则返回false
	bool operator != (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return <返回true，否则返回false
	bool operator < (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return <=返回true，否则返回false
	bool operator <= (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return >返回true，否则返回false
	bool operator > (const CTime& time) const;

	/// 时间比较
	/// \param time 相比较的时间
	/// \return >=返回true，否则返回false
	bool operator >= (const CTime& time) const;
	
	/// 时间格式化
	/// \param buf 字符串缓冲，一定要足够大
	/// \param format 格式化字符串，如"yyyy-MM-dd HH:mm:ss tt"
	/// yy = 年，不带世纪 yyyy = 年，带世纪
	/// M = 非0起始月 MM = 0起始月 MMMM = 月名称
	/// d = 非0起始日 dd = 0起始日
	/// H = 非0起始24小时 HH = 0起始24小时 h = 非0起始12小时 hh = 0起始12小时
	/// tt = 显示上午或下午
	/// 但日期分隔符， 年月日顺序，小时制式由统一的格式决定。
	void format(char* buf, const char *format) const;

	/// 得到本地当前系统时间
	static CTime getCurrentTime();

	/// 设置本地当前系统时间
	static void setCurrentTime(const CTime& time);

	/// 得到从系统启动到现在的毫秒数
	static uint64 getCurrentMilliSecond();

	/// 得到从系统启动到现在的微秒数
	static uint64 getCurrentMicroSecond();

	/// 让调用线程阻塞一段时间
	/// \param milliSeconds 期望阻塞的毫秒数
	static void sleep(int milliSeconds);

	/// 设置时间格式，会影响Format的输出的字符串格式，如"yyyy-MM-dd HH:mm:ss"
	static void setFormat(const std::string format);

	/// 获取时间格式
	static const std::string getFormat();

	/// 获取日期格式
	static int getDateFormat();

	/// 获取当前是否是12小时制
	static bool get12Hour();

	/// 获取日期分割符
	static char getSpliter();
	
public:
	static const CTime minTime; ///< 有效的最小时间
	static const CTime maxTime; ///< 有效的最大时间

private:
	
	static std::string m_format;
	static int m_dateFormat;
	static char m_dateSeparator;
	static bool m_12hour;
};

}///end of namespace

#endif // __TIME_WRAPPER_H__






