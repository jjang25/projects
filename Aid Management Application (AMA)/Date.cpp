// Date.cpp
// Jongwon Jang

#include <iostream>
#include "Date.h"
using namespace std;

namespace aid 
{
	int Date::mdays(int mon, int year)const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int errorCode) 
	{	
		switch (errorCode)
		{
			case 0:
				_error = NO_ERROR;
				break;
			case 1:
				_error = CIN_FAILED;
				break;
			case 2:
				_error = DAY_ERROR;
				break;
			case 3:
				_error = MON_ERROR;
				break;
			case 4:
				_error = YEAR_ERROR;
				break;
			case 5:
				_error = PAST_ERROR;
				break;
		
		}

	}

	Date::Date() 
	{
		_year = 0;
		_month = 0;
		_day = 0;
		_error = NO_ERROR;
		_comparator = 0;
	}

	Date::~Date() {};

	Date::Date(int ye, int mo, int da)
	{
		if (ye<min_year || ye > max_year)
		{
			*this = Date();
			errCode(YEAR_ERROR);
		}
		else if (mo < 1 || mo >12)
		{
			*this = Date();
			errCode(MON_ERROR);

		}
		else if (da<1 || da > mdays(mo, ye))
		{
			*this = Date();
			errCode(DAY_ERROR);
		}
		else if ((ye * 372 + mo * 31 + da )< min_date)
		{
			*this = Date();
			errCode(PAST_ERROR);
		}
		else
		{
			_year = ye;
			_month = mo;
			_day = da;
			_comparator = ye * 372 + mo * 31 + da;
			errCode(NO_ERROR);
		}
		
	}

	bool Date::operator==(const Date& rhs) const 
	{
		bool compare;
		if (!bad() && !rhs.bad()) 
		{
			compare = _comparator == rhs._comparator;
		}
		else 
		{
			compare = false;
		}
		return compare;
		
	}

	bool Date::operator!=(const Date& rhs) const
	{
		bool compare;
		if (!bad() && !rhs.bad())
		{
			compare = _comparator != rhs._comparator;
		}
		else 
		{
			compare = false;
		}
		return compare;
	}
	
	bool Date::operator<(const Date& rhs) const 
	{
		bool compare;
			if (!bad() && !rhs.bad()) 
			{
				compare = _comparator < rhs._comparator;
			}
			else 
			{
				compare = false;
			}
			return compare;
	}

	bool Date::operator>(const Date& rhs) const
	{
		bool compare;
			if (!bad() && !rhs.bad())
			{
				compare = _comparator > rhs._comparator;
			}
			else 
			{
				compare = false;
			}
			return compare;
	}

	bool Date::operator<= (const Date& rhs) const 
	{
		bool compare;
			if (!bad() && !rhs.bad()) 
			{
				compare = _comparator <= rhs._comparator;
			}
			else 
			{
				compare = false;
			}
			return compare;
	}

	bool Date::operator>=(const Date& rhs) const 
	{
		bool compare;
			if (!bad() && !rhs.bad()) 
			{
				compare = _comparator >= rhs._comparator;
			}
			else 
			{
				compare = false;
			}
			return compare;
	}

	int Date::errCode() const
	{
		return _error;
	}

	bool Date::bad() const 
	{
		return !_error == NO_ERROR;
	}

	std::istream& Date::read(std::istream& istr)
	{
		char c;
		int tyear, tmonth, tday;
		
		istr.clear();
		istr >> tyear >> c >> tmonth >> c >> tday;
		
		if (istr.fail())
			errCode(CIN_FAILED);
		else 
		{
			*this = Date(tyear, tmonth, tday);
		}		
		return istr;
		
	}
	
	std::ostream& Date::write(std::ostream& ostr) const
	{
		ostr.fill('0');		
		ostr << _year << "/";
		ostr.width(2);
		ostr << _month << "/";
		ostr.width(2); 
		ostr << _day;
		ostr.fill(' ');
		return ostr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Date& date )
	{
		date.write(ostr);
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, Date& date) 
	{
		date.read(istr);
		return istr;

	}
}
