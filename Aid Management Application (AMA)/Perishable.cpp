// iGood.h
// Jongwon Jang

#include "Perishable.h"

namespace aid {

	Perishable::Perishable() :Good('P') 
	{
		isClear();
	}

	std::fstream& Perishable::store(std::fstream& file, bool newline) const
	{
		Good::store(file, false);
		file << "," << perDate;
		if (newline)
			file << std::endl;
		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) 
	{
		Good::load(file);
		perDate.read(file);
		file.ignore();
		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		Good::write(os, linear);
		if (isClear() && !isEmpty()) 
		{
			if (linear)
				perDate.write(os);
			else 
			{
				os << std::endl << " Expiry date: ";
				perDate.write(os);
			}
		}

		return os;
	}

	std::istream& Perishable::read(std::istream& is) 
	{
		is.clear();
		Good::read(is);
		if (isClear()) 
		{
			std::cout << " Expiry date (YYYY/MM/DD): ";
			is >> perDate;
		}
		if (perDate.bad()) 
		{
			is.setstate(std::ios::failbit);
			switch (perDate.errCode())
			{
			case CIN_FAILED:
				this->message("Invalid Date Entry");
				break;
			case YEAR_ERROR:
				message("Invalid Year in Date Entry");
				break;
			case MON_ERROR:
				message("Invalid Month in Date Entry");
				break;
			case DAY_ERROR:
				message("Invalid Day in Date Entry");
				break;
			case PAST_ERROR:
				message("Invalid Expiry in Date Entry");
			}
		}
		return is;
	}

	const Date& Perishable::expiry() const
	{
		return perDate;
	}

	iGood* CreateProduct(char tag) 
	{
		if (tag == 'N' || tag == 'n')
		{
			return new Good();
		}
		else if (tag == 'P' || tag == 'p')
		{
			return new Perishable();
		}
		else
			return nullptr;
	}
}



