// Date.h
// Jongwon Jang

#ifndef AID_DATE_H
#define AID_DATE_H

#define NO_ERROR 0
#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3
#define YEAR_ERROR 4
#define PAST_ERROR 5

namespace aid 
{
	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;
  
	class Date 
	{
		int _year;
		int _month;
		int _day;
		int _comparator;
		int _error;
		int mdays(int, int) const;
		void errCode(int errorCode);
  public:
		Date();
		~Date();
		Date(int, int, int);
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<= (const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};
  std::ostream& operator<<(std::ostream& ostr, const Date& date);
  std::istream& operator>>(std::istream& istr, Date& date);
}

#endif