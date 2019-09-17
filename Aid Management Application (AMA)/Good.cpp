// Good.cpp
// Jongwon Jang

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Good.h"
using namespace std;

namespace aid
{

	Good::Good(char type)
	{
		_type = type;
		_sku[0] = '\0';
		_unit[0] = '\0';
		_name = nullptr;
		_qty = 0;
		_needed = 0;
		_price = 0.0;
		_taxable = false;
	}

	Good::Good(const char* sku, const char* name, const char* unit, int quantity, bool taxable, double price, int needed)
	{
		bool notNull = sku != nullptr && name != nullptr && unit != nullptr;

		if (notNull)
		{
			strncpy(_sku, sku, strlen(sku));
			_sku[strlen(sku)] = '\0';

			Good::name(name);

			strncpy(_unit, unit, strlen(unit));
			_unit[strlen(unit)] = '\0';
		}

		_qty = quantity;
		_taxable = taxable;
		_price = price;
		_needed = needed;
	}

	Good::Good(const Good& other)
	{
		*this = other;
	}

	Good& Good::operator=(const Good& other)
	{
		if (this != &other)
		{
			int sku_l = strlen(other._sku);
			int unit_l = strlen(other._unit);

			_type = other._type;
			_qty = other._qty;
			_needed = other._needed;
			_price = other._price;
			_taxable = other._taxable;

			name(other._name);

			strncpy(_sku, other._sku, sku_l);
			_sku[sku_l] = '\0';

			strncpy(_unit, other._unit, unit_l);
			_unit[unit_l] = '\0';
		}

		return *this;
	}

	Good::~Good()
	{
		delete[] _name;
	}
	std::fstream& Good::store(std::fstream& file, bool newLine) const
	{
		file << _type << ',' << _sku << ',' << _name << ',' << _unit << ',' << _taxable << ',' << _price << ',' << _qty << ',' << _needed;
		if (newLine)
			file << endl;
		return file;
	}
	std::fstream& Good::load(std::fstream& file)
	{
		char sku_[max_sku_length];
		char name_[max_name_length];
		char unit_[max_unit_length];
		double price;
		int qty, needed;
		char tax;
		bool taxable;

		if (file.is_open())
		{
			file.getline(sku_, max_sku_length, ',');
			sku_[strlen(sku_)] = '\0';

			file.getline(name_, max_name_length, ',');
			name_[strlen(name_)] = '\0';

			file.getline(unit_, max_unit_length, ',');
			unit_[strlen(unit_)] = '\0';

			file >> tax;

			if (tax == '1')
				taxable = true;
			else if (tax == '0')
				taxable = false;

			file.ignore();

			file >> price;
			file.ignore();

			file >> qty;
			file.ignore();

			file >> needed;
			file.ignore();

			*this = Good(sku_, name_, unit_, qty, taxable, price, needed);
		}

		return file;
	}
	std::ostream& Good::write(std::ostream& os, bool linear) const
	{
		if (!(er.isClear()))
		{
			os << er.message();
		}
		else if (isEmpty() && linear)
		{

		}
		else if (linear)
		{
			os << setw(max_sku_length) << left << _sku << '|'
				<< setw(20) << left << _name << '|'
				<< setw(7) << right << fixed << setprecision(2) << itemCost() << '|'
				<< setw(4) << right << _qty << '|'
				<< setw(10) << left << _unit << '|'
				<< setw(4) << right << _needed << '|';
		}
		else
		{
			os << " Sku: " << _sku << endl
				<< " Name (no spaces): " << _name << endl
				<< " Price: " << _price << endl;

			if (_taxable)
				os << " Price after tax: " << itemCost() << endl;
			else
			{
				os << " Price after tax:  N/A" << endl;
			}

			os << " Quantity on Hand: " << _qty << ' ' << _unit << endl;
			os << " Quantity needed: " << _needed;
		}

		return os;
	}
	std::istream& Good::read(std::istream& is)
	{
		char taxed;
		char* address = new char[max_name_length + 1];
		int qty, need;
		double _price;

		if (!is.fail())
		{
			cout << " Sku: ";
			is >> _sku;
			cin.ignore();

			cout << " Name (no spaces): ";
			is >> address;
			name(address);

			cout << " Unit: ";
			is >> _unit;

			cout << " Taxed? (y/n): ";
			is >> taxed;

			if (!is.fail())
			{
				er.clear();

				if (taxed)
				{
					bool y_valid = taxed == 'y' || taxed == 'Y';
					bool n_valid = taxed == 'n' || taxed == 'N';

					if (y_valid)
						_taxable = true;

					if (n_valid)
						_taxable = false;

					if (!(y_valid || n_valid))
					{
						is.setstate(std::ios::failbit);
						er.message("Only (Y)es or (N)o are acceptable");
						return is;
					}
				}
			}
			else
			{
				is.setstate(std::ios::failbit);
				er.message("Only (Y)es or (N)o are acceptable");
				return is;
			}

			cout << " Price: ";
			is >> _price;

			if (is.fail())
			{
				er.clear();
				is.setstate(ios::failbit);
				er.message("Invalid Price Entry");
				return is;
			}
			else
				price(_price);

			cout << " Quantity on hand: ";
			is >> qty;


			if (is.fail())
			{
				er.clear();
				er.message("Invalid Quantity Entry");
				is.setstate(ios::failbit);
				return is;
			}
			else
				quantity(qty);

			cout << " Quantity needed: ";
			is >> need;

			if (is.fail())
			{
				er.clear();
				er.message("Invalid Quantity Needed Entry");
				is.setstate(ios::failbit);
				return is;
			}
			else
				needed(need);

			if (!is.fail())
			{
				er.clear();
			}
		}

		return is;
	}
	bool Good::operator==(const char* rhs) const
	{
		if (rhs == sku())
			return true;
		else
			return false;
	}
	double Good::total_cost() const
	{
		return _qty * itemCost();
	}
	void Good::quantity(int quantity)
	{
		_qty = quantity;
	}
	void Good::price(double price)
	{
		_price = price;
	}
	void Good::needed(int needed)
	{
		_needed = needed;
	}
	bool Good::isEmpty() const
	{
		if (_name == nullptr)
			return true;
		else
			return false;
	}
	char Good::type() const
	{
		return _type;
	}
	int Good::qtyNeeded() const
	{
		return _needed;
	}
	int Good::quantity() const
	{
		return _qty;
	}
	bool Good::operator>(const char* rhs) const
	{
		if (strcmp(_sku, rhs) > 0)
			return true;
		else
			return false;
	}
	bool Good::operator>(const iGood& rhs) const
	{
		if (strcmp(_name, rhs.name()) > 0)
			return true;
		else
			return false;
	}
	int Good::operator+=(int units)
	{
		if (units > 0)
		{
			_qty += units;
			return _qty;
		}
		else
			return _qty;
	}
	void Good::name(const char* name)
	{
		if (name != nullptr)
		{
			int length = strlen(name);

			_name = new char[length + 1];
			for (int i = 0; i < length; i++)
			{
				_name[i] = name[i];
			}
			_name[length] = '\0';
		}
		else if (name == nullptr)
		{
			delete[] _name;
			_name = nullptr;
		}
	}

	const char* Good::name() const
	{
		if (_name != nullptr)
			return _name;
		else
			return nullptr;
	}
	const char* Good::sku() const
	{
		return _sku;
	}
	const char* Good::unit() const
	{
		return _unit;
	}
	bool Good::taxed() const
	{
		return _taxable;
	}
	double Good::itemPrice() const
	{
		return _price;
	}
	double Good::itemCost() const
	{
		if (_taxable)
			return itemPrice() * (tax_rate + 1);
		else
			return itemPrice();
	}
	void Good::message(const char* errorMessage)
	{
		if (errorMessage != nullptr)
			er.message(errorMessage);
	}
	bool Good::isClear() const
	{
		return er.isClear();
	}
	std::ostream& operator<<(std::ostream& os, const iGood& other)
	{
		return other.write(os, true);
	}
	std::istream& operator>>(std::istream& is, iGood& other)
	{
		return other.read(is);
	}

	double operator+=(double& pcost, const Good& g)
	{
		pcost += g.total_cost();
		return pcost;
	}
}