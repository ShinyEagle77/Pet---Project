#pragma once

#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

// Possibly add Check-Function for constructor

class CarModel
{
public:
	CarModel(const string& new_name, const string& new_type, const  int& new_powerValue) // DefaultConstructor, all numbers are my own limits for a CarParameters;
	{
		if (new_name.size() > 12 || new_name.empty())
		{
			throw out_of_range("Model name is incorrect: " + new_name);
		}
		else if (new_type.size() > 8 || new_type.empty())
		{
			throw out_of_range("Type name is incorrect: " + new_type);
		}
		else if (new_powerValue > 2500 || new_powerValue < 250)
		{
			throw out_of_range("Power Value is incorrect: " + to_string(new_powerValue));
		}
		name = new_name;
		type = new_type;
		powerValue = new_powerValue;
	}

	string GetCarModelName() const;
	string GetCarType() const;
	int GetCarPowerValue() const;

private:
	string name;
	string type;
	int powerValue;
};

ostream& operator << (ostream& stream, const CarModel& carmodel);

bool operator < (const CarModel& r, const CarModel& l);

bool operator < (const string& lhs, const CarModel& rhs);

bool operator < (const CarModel& lhs, const string& rhs);