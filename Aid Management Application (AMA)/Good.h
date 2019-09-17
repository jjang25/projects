// Good.h
// Jongwon Jang

#ifndef AID_GOOD_H
#define AID_GOOD_H

#include <iostream>
#include "iGood.h"
#include "Error.h"

namespace aid
{
	const int max_sku_length = 7;
	const int max_name_length = 75;
	const int max_unit_length = 10;
	const double tax_rate = 0.13;

	class Good : public iGood
	{
		char _type;
		char _sku[max_sku_length];
		char _unit[max_unit_length];
		char* _name;
		int _qty;
		int _needed;
		double _price;
		bool _taxable;

	protected:
		Error er;
		void name(const char* name);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char* errorMessage);
		bool isClear() const;

	public:
		Good(char type = 'N');
		Good(const char* sku, const char* name, const char* unit, int quantity = 0, bool taxable = true, double price = 0.0, int needed = 0);
		Good(const Good& other);
		Good& operator=(const Good& other);
		~Good();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char* rhs) const;
		double total_cost() const;
		void quantity(int quantity);
		void price(double price);
		void needed(int needed);
		bool isEmpty() const;
		char type() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char* rhs) const;
		bool operator>(const iGood& rhs) const;
		int operator+=(int units);
	};
	std::ostream& operator<<(std::ostream& os, const iGood& other);
	std::istream& operator>>(std::istream& is, iGood& other);
	double operator+=(double& pcost, const Good& g);
}

#endif 