#include "parse_funcs.h"

CarModel ParseCarModel(const string& carmodel, const string& cartype, const int& powerValue)
{
	stringstream car_stream(carmodel);
	stringstream car_type(cartype);
	string name, type;
	car_stream >> name;

	for (const auto& k : name)
	{
		if (isalpha(k) == 0) // Checking if string is containing wrong symbols
		{
			throw out_of_range("Car name contains wrong symbols: " + carmodel);
		}
	}

	car_type >> type;

	for (const auto& k : type)
	{
		if (isalpha(k) == 0)
		{
			throw out_of_range("Car type contains wrong symbols: " + cartype);
		}
	}

	return { name, type, powerValue }; // Construct a new CarModel
}

string ParseCompanyName(const string& _companyname)
{
	stringstream company_stream(_companyname);
	string name;
	company_stream >> name;

	if (name.size() > 15 || name.empty())
	{
		throw out_of_range("Company name is too long: " + _companyname);
	}

	for (const auto& k : name)
	{
		if (isalpha(k) == 0)
		{
			throw out_of_range("Company name contains wrong symbols: " + _companyname);
		}
	}

	return { name };
}
