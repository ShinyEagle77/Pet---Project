// Simple database that contains a container with a companyname as a key, and a set of CarModels as value;
// Next commands are available:
// Add "companyname" - Add a new company with empty set of carmodels list,
// Add "companyname" "carname" "cartype" "carpowervalue(int)" - Add a new company with a car (name, type, powervalue),
// Print - prints all the database,
// Print "companyname" - to print all models for this company,
// Print "cartype" - to print all cars with this type,
// Print "carname" - to print an information about car,
// Del "All" - to clear all database,
// Del "companyname" - to delete a company, also couts number of deleted cars,
// Del "companyname" "carname" - to delete an exact car from a company,
// Change "oldcompanyname" "newcompanyname" - to change a companyname, new company would has all cars of old company,
// Change "companyname" "oldcarname" "newcarname" - to change a carmodelname inside a company.

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <exception>
#include <set>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <utility>

using namespace std;

enum class WhatFound
{
	Nothing,
	Car,
	Type,
	Companyname,
	OldCompanyNameOnly,
	BothCompaniesAreExist,
	OldCarNameOnly,
	BothCarsAreExist,
};

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

	string GetCarModelName() const
	{
		return name;
	}
	string GetCarType() const
	{
		return type;
	}
	int GetCarPowerValue() const
	{
		return powerValue;
	}

private:
	string name;
	string type;
	int powerValue;
};

ostream& operator << (ostream& stream, const CarModel& carmodel)
{
	stream << carmodel.GetCarModelName() << ' ' << carmodel.GetCarType()
		<< ' ' << carmodel.GetCarPowerValue() << " hp";
	return stream;
}

bool operator < (const CarModel& r, const CarModel& l)
{
	return (r.GetCarModelName() < l.GetCarModelName());
}

bool operator < (const string& lhs, const CarModel& rhs)
{
	return lhs < rhs.GetCarModelName();
}

bool operator < (const CarModel& lhs, const string& rhs)
{
	return lhs.GetCarModelName() < rhs;
}

class Database
{
public:

	void AddModel(const string& company, const CarModel& carmodel)
	{
		database[company].insert(carmodel);
	}

	void AddCompany(const string& company)
	{
		database[company];
	}

	void PrintAllModels() const
	{
		if (database.empty())
		{
			cout << "No models in database" << endl;
		}
		for (const auto& i : database)
		{
			cout << i.first << ": ";
			for (const auto& k : i.second)
			{
				static uint16_t s = 0;
				++s;
				if (s < i.second.size())		// If there are several models in a row, adds ',' between them for a better printing. (Bayonetta, Aventador, California)
				{
					cout << k.GetCarModelName() << ", ";
				}
				else if (s == i.second.size())
				{
					cout << k.GetCarModelName();
				}

			}
			cout << endl;
		}
	}

	void PrintCompany(const string& companyname) const
	{
		if (database.count(companyname) == 0)
		{
			cout << "No company in database with name: " + companyname << endl;
		}
		else
		{
			for (const auto& k : database)
			{
				if (k.second.empty()) // Checking if company has any cars
				{
					cout << companyname << " hasn't any cars" << endl;
				}
				else if (k.first == companyname)
				{
					
					cout << companyname << ": ";
					for (const auto& i : k.second) // If there are several models in a row, adds ',' between them for a better printing. (Bayonetta, Aventador, California)
					{
						static uint16_t s = 0;
						++s;

						if (s < k.second.size())
						{
							cout << i.GetCarModelName() << ", ";
						}

						else if (s == k.second.size())
						{
							cout << i.GetCarModelName();
						}

					}
					cout << endl;
				}
			}
		}

	}

	void PrintType(const string& type) const
	{
		vector <string> typebase; // Creating a temporary storage for the all cars which has a type == sinput;
		for (const auto& k : database)
		{
			for (const auto& i : k.second)
			{
				if (i.GetCarType() == type)
				{

					typebase.push_back(i.GetCarModelName());

				}
			}
		}

		cout << type << ": "; // Printing this vector, which storage all cars with type == sinput;
		
		for (const auto& s : typebase)
		{
			static uint16_t x = 0;
			++x;
			if (x < typebase.size()) 
			{
				cout << s << ", ";
			}
			else if (x == typebase.size())
			{
				cout << s;
			}

		}

		cout << endl;

	}

	void PrintCarInformation(const string& sinput) const
	{
		for (const auto& k : database)
		{
			for (const auto& i : k.second)
			{
				if (i.GetCarModelName() == sinput)
				{
					cout << i.GetCarModelName() << " made by " << k.first << " with " << i.GetCarType() << " type" << " and " << i.GetCarPowerValue() << "hp" << endl;
				}
			}
		}
	}

	unsigned int DeleteCompany(const string& companyname)
	{
		if (database.find(companyname) != database.end()) // If Company with companyname is found
		{
			const unsigned int deletedCars = database[companyname].size(); // Remember a quantity value for all models which company has,
			database.erase(companyname);
			return deletedCars; // Returning quantity value for a better print format;
		}
		else
		{
			return 0; // Else return 0;
		}
	}

	bool DeleteCarModel(const string& _companyname, const string& _carmodel) // Returns true if it is successful to delete a car, else return false;
	{
		if (auto company_it = database.find(_companyname); company_it != database.end())
		{
			if (auto carmodel_it = company_it->second.find(_carmodel); carmodel_it != company_it->second.end())
			{
				company_it->second.erase(carmodel_it);
				return true;
			}
		}
		else
		{
			return false;
		}

		return false;
	}

	unsigned int DeleteAll(const string& string)
	{
		const unsigned int count = database.size(); // Remember a quantity value of companies in database;

		if (database.empty())
		{
			return 0;
		}
		else
		{
			database.clear(); 
			return count;
		}

	}

	WhatFound CheckStringToPrint(const string& sinput)
	{
		for (const auto& k : database)
		{
			if (k.first == sinput)
			{
				return WhatFound::Companyname;
			}
			else // If hasn't found a company with companyname to print, go ahead
			{
				for (const auto& i : k.second)
				{
					if (i.GetCarType() == sinput)
					{
						return WhatFound::Type;
					}
					else if (i.GetCarModelName() == sinput)
					{
						return WhatFound::Car;
					}
				}
			}
		}
		return WhatFound::Nothing;
	}

	uint16_t CheckStringToChangeCompany(const string& sourcename, const string& newcompanyname)
	{
		uint16_t result = 0;
		if (database.find(sourcename) != database.end())
		{
			result = 1;  // Company with oldname found
		}
		if (database.find(sourcename) != database.end() && database.find(newcompanyname) != database.end())
		{
			result = 2; // Companies with oldname and newname found
		}

		return result;
	}

	uint16_t CheckStringToChangeCar(const string& companyname, const string& oldcarname, const string& newcarname)
	{
		uint16_t result = 0;
		for (const auto& k : database)
		{
			if (k.first == companyname)
			{
				if (k.second.find(oldcarname) != k.second.end())
				{
					result = 1; // Car with oldname found
				}
				if (k.second.find(oldcarname) != k.second.end() && k.second.find(newcarname) != k.second.end())
				{
					result = 2; // Car with oldname and newname found
				}
			}
		}

		return result;
		
	}

	WhatFound ChangeCarInCompany (const string& companyname, const string& oldcarname, const string& newcarname)
	{
		const uint16_t result = CheckStringToChangeCar(companyname, oldcarname, newcarname);
		if (result == 0)
		{
			return WhatFound::Nothing;
		}
		else if (result == 1)
		{
			for (const auto& k : database)
			{
				if (k.first == companyname)
				{
					for (const auto& i : k.second)
					{
						if (i.GetCarModelName() == oldcarname)
						{
							CarModel newCar{ newcarname, i.GetCarType(), i.GetCarPowerValue() }; // Creating a new car with same parameters as an old car, except for
							database[companyname].insert(newCar);								 // CarType and PowerValue,
							if (DeleteCarModel(companyname, oldcarname))						 // Then delete an old car
							{
								return WhatFound::OldCarNameOnly;
							}
						}
					}
				}
			}
			
		}
		else if (result == 2)
		{
			return WhatFound::BothCarsAreExist;
		}

		return WhatFound::Nothing;
	}

	WhatFound ChangeCompany(const string& name, const string& newname)
	{
		
		const uint16_t result = CheckStringToChangeCompany(name, newname);
		if (result == 0)
		{
			return WhatFound::Nothing;
		}
		else if (result == 1)
		{

			auto node = database.extract(name);
			node.key() = newname;
			database.insert(move(node));

			database.erase(name);
			return WhatFound::OldCompanyNameOnly;
		}
		else if (result == 2)
		{
			return WhatFound::BothCompaniesAreExist;
		}

		return WhatFound::Nothing;
	}

private:
	map<string, set<CarModel, less<>>> database;
};

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

int main()
{
	try
	{
		Database base;
		string command;
		while (getline(cin, command))
		{
			stringstream stream(command);

			string operation;
			stream >> operation;

			if (operation == "Add")
			{
				string _companyname;

				stream >> _companyname;
				if (stream.eof())			// If stream reached end of the string, checking input
				{
					if (_companyname.empty()) // If command Add only was inputed
					{
						cout << "Command need an argument, avaliable: companyname carmodel cartype carpowervalue, companyname" << endl;
					}
					else
					{
						const string companyname = ParseCompanyName(_companyname);
						base.AddCompany(companyname);
					}

				}
				else
				{
					string _carName, _carType;
					int _carPowerValue;

					stream >> _carName >> _carType >> _carPowerValue;

					const string companyname = ParseCompanyName(_companyname);
					const CarModel car = ParseCarModel(_carName, _carType, _carPowerValue);

					base.AddModel(companyname, car);
				}

			}
			else if (operation == "Print")
			{
				string sinput;
				stream >> sinput;

				if (sinput.empty())
				{
					base.PrintAllModels();
				}
				else
				{
					WhatFound result = base.CheckStringToPrint(sinput);
					if (result == WhatFound::Companyname)
					{
						base.PrintCompany(sinput);
					}
					else if (result == WhatFound::Type)
					{
						base.PrintType(sinput);
					}
					else if (result == WhatFound::Car)
					{
						base.PrintCarInformation(sinput);
					}
					else if (result == WhatFound::Nothing)
					{
						cout << "No such a type or a company in database: " + sinput << endl;
					}
				}

			}
			else if (operation == "Del")
			{
				string _companyname;
				stream >> _companyname;

				if (_companyname.empty())
				{
					cout << "Command need an argument, available : companyname carmodel, All " << endl;
				}
				else
				{
					const string companyname = ParseCompanyName(_companyname);

					if (companyname == "All")
					{
						const unsigned int count = base.DeleteAll(companyname);
						if (count > 0)
						{
							cout << "All database was deleted with " << count << " companies" << endl;
						}
						else if (count == 0)
						{
							cout << "Database is empty, nothing to clear" << endl;
						}
					}

					else
					{
						string _carname;

						if (!stream.eof())
						{
							stream >> _carname;
						}

						if (_carname.empty())
						{
							const unsigned int deletedCars = base.DeleteCompany(companyname);

							if (deletedCars > 0)
							{
								cout << companyname << " was successfully deleted with " << deletedCars << " cars" << endl;
							}

							else if (deletedCars == 0)
							{
								cout << "Company name " << companyname << " wasn't found" << endl;
							}
						}

						else
						{
							if (base.DeleteCarModel(companyname, _carname))
							{
								cout << _carname << " made by a " << companyname << " was successfully deleted " << endl;
							}
							else
							{
								cout << companyname << " has no car model named " << _carname << endl;
							}
						}
					}
				}
			}

			else if (operation == "Change")
			{
				string _companyname;
				stream >> _companyname;

				if (_companyname.empty())
				{
					cout << "Command need argument, available: oldcompanyname newcompanyname, companyname oldcarname newcarname" << endl;
				}
				else
				{
					string _newcompanyname, _newcarname;
					stream >> _newcompanyname >> _newcarname;
					const string companyname = ParseCompanyName(_companyname);

					if (_newcompanyname.empty())
					{
						cout << "Write as a second argument a NEW companyname, or a oldcarname and a newcarname made by companyname" << endl;
					}
					else if (_newcarname.empty())
					{
						const string newcompanyname = ParseCompanyName(_newcompanyname);

						const WhatFound result = base.ChangeCompany(_companyname, _newcompanyname);

						if (result == WhatFound::Nothing)
						{
							cout << "Company named " << _companyname << " not found" << endl;
						}
						else if (result == WhatFound::OldCompanyNameOnly)
						{
							cout << "Company named " << _companyname << " changed her name to " << _newcompanyname << endl;
						}
						else if (result == WhatFound::BothCompaniesAreExist)
						{
							cout << _companyname << " and " << _newcompanyname << " already exist " << endl;
						}
					}
					else
					{
						if (base.CheckStringToChangeCompany(companyname, _newcompanyname) == 0)
						{
							cout << "Company named " << _companyname << " not found" << endl;
						}
						else
						{
							const string _oldcarname = _newcompanyname; // Variable name changed for better readability
							const WhatFound result = base.ChangeCarInCompany(_companyname, _oldcarname, _newcarname);
							
							if (result == WhatFound::Nothing)
							{
								cout << "Car name " << _oldcarname << " not found" << endl;
							}
							else if (result == WhatFound::OldCarNameOnly)
							{
								cout << "Car named " << _oldcarname << " changed name to " << _newcarname << endl;
							}
							else if (result == WhatFound::BothCarsAreExist)
							{
								cout << _oldcarname << " and " << _newcarname << " already exist" << endl;
							}
						}
						
					}

				}
			}

			else if (!operation.empty())
			{
				throw logic_error("Unknown command: " + command);
			}
		}
	}
	catch (exception& ex) {

		cout << ex.what() << endl;
	}

	return 0;

}
