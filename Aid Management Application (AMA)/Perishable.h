// Perishable.h
// Jongwon Jang

#ifndef AID_PERISHABLE_H
#define AID_PERISHABLE_H

#include "Good.h"
#include "Date.h"

namespace aid
{
	class Perishable : public Good 
	{
		Date perDate;
	public:
		Perishable();
		~Perishable() {}
		std::fstream& store(std::fstream& file, bool newline = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;

	};
	iGood* CreateProduct(char tag);
}

#endif