#ifndef __TIME_WRAPPER_H__
#define __TIME_WRAPPER_H__

#include "types.h"
#include <string>
namespace THINK{
/// ϵͳʱ��ṹ
typedef struct SYSTEM_TIME{
	int  year;///< �ꡣ   
	int  month;///< �£�January = 1, February = 2, and so on.   
	int  day;///< �ա�   
	int  wday;///< ���ڣ�Sunday = 0, Monday = 1, and so on   
	int  hour;///< ʱ��   
	int  minute;///< �֡�   
	int  second;///< �롣   
	int  isdst;///< ����ʱ��ʶ��   
}SYSTEM_TIME;

/// \class CTime
/// \brief ʱ���࣬ʵ���˱���ʱ���ȡ�����㣬��ʽ�������ӡ�Ƚӿ�
class CTime : public SYSTEM_TIME
{
public:
	enum DataFormat
	{
		ymd,
		mdy,
		dmy
	};

	/// ȱʡ���캯��
	CTime( );

	/// ���ʱ�乹�캯��
	CTime(uint64 time);

	/// ��ͨʱ�乹�캯��
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
	
	/// �õ����ʱ�䣬���ʱ��ָ��1900-1-1 00:00:00��ĳ��ʱ�̾���������
	/// \return ���ʱ��
	uint64 makeTime() const;

	/// �ֽ����ʱ��
	/// \param time ���ʱ��
	void breakTime(uint64 time);

	/// ʱ�����
	/// \param seconds ���ڵ�����
	/// \return ���ں��µ�ʱ�����
	CTime operator +( int64 seconds ) const;

	/// ʱ�����
	/// \param seconds ���ڵ�����
	/// \return ���ں��µ�ʱ�����
	CTime operator -( int64 seconds ) const;

	/// ʱ�������
	/// \param time ��Ƚϵ�ʱ��
	/// \return �ȽϵĽ����Ϊ(*this - time)�õ�������
	int64 operator -( const CTime& time ) const;

	/// ʱ�����
	/// \param seconds ���ڵ�����
	/// \return ������
	CTime& operator +=( int64 seconds );

	/// ʱ�����
	/// \param seconds ���ڵ�����
	/// \return ������
	CTime& operator -=( int64 seconds );

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return ��ȷ���true�����򷵻�false
	bool operator == (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return ���ȷ���true�����򷵻�false
	bool operator != (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return <����true�����򷵻�false
	bool operator < (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return <=����true�����򷵻�false
	bool operator <= (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return >����true�����򷵻�false
	bool operator > (const CTime& time) const;

	/// ʱ��Ƚ�
	/// \param time ��Ƚϵ�ʱ��
	/// \return >=����true�����򷵻�false
	bool operator >= (const CTime& time) const;
	
	/// ʱ���ʽ��
	/// \param buf �ַ������壬һ��Ҫ�㹻��
	/// \param format ��ʽ���ַ�������"yyyy-MM-dd HH:mm:ss tt"
	/// yy = �꣬�������� yyyy = �꣬������
	/// M = ��0��ʼ�� MM = 0��ʼ�� MMMM = ������
	/// d = ��0��ʼ�� dd = 0��ʼ��
	/// H = ��0��ʼ24Сʱ HH = 0��ʼ24Сʱ h = ��0��ʼ12Сʱ hh = 0��ʼ12Сʱ
	/// tt = ��ʾ���������
	/// �����ڷָ����� ������˳��Сʱ��ʽ��ͳһ�ĸ�ʽ������
	void format(char* buf, const char *format) const;

	/// �õ����ص�ǰϵͳʱ��
	static CTime getCurrentTime();

	/// ���ñ��ص�ǰϵͳʱ��
	static void setCurrentTime(const CTime& time);

	/// �õ���ϵͳ���������ڵĺ�����
	static uint64 getCurrentMilliSecond();

	/// �õ���ϵͳ���������ڵ�΢����
	static uint64 getCurrentMicroSecond();

	/// �õ����߳�����һ��ʱ��
	/// \param milliSeconds ���������ĺ�����
	static void sleep(int milliSeconds);

	/// ����ʱ���ʽ����Ӱ��Format��������ַ�����ʽ����"yyyy-MM-dd HH:mm:ss"
	static void setFormat(const std::string format);

	/// ��ȡʱ���ʽ
	static const std::string getFormat();

	/// ��ȡ���ڸ�ʽ
	static int getDateFormat();

	/// ��ȡ��ǰ�Ƿ���12Сʱ��
	static bool get12Hour();

	/// ��ȡ���ڷָ��
	static char getSpliter();
	
public:
	static const CTime minTime; ///< ��Ч����Сʱ��
	static const CTime maxTime; ///< ��Ч�����ʱ��

private:
	
	static std::string m_format;
	static int m_dateFormat;
	static char m_dateSeparator;
	static bool m_12hour;
};

}///end of namespace

#endif // __TIME_WRAPPER_H__






