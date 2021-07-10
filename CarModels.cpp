﻿// Add - Add a new company with a car (name, type, powervalue);
// Print - if arguments are empty, prints all the database. Also available:
// Print "companyname" (to print all models for this company)
// Print "cartype" - print all cars with this type
// Print "carname" - print an information about car;

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <exception>
#include <set>
#include <iomanip>
#include <sstream>


using namespace std;


//class Owner
//{
//public:
//	Owner(const string& new_name, const string& new_surname, const int& new_age) // Default constructor for class Owner;
//	{
//		if (new_name.size() > 30 || new_name.empty()) // Checking for valid name, surname and age;
//		{
//			throw out_of_range("Name has a wrong format: " + new_name);
//		}
//		else if (new_surname.size() > 45 || new_surname.empty())
//		{
//			throw out_of_range("Surname has a wrong format: " + new_surname);
//		}
//		else if (new_age > 100 || new_age < 1)
//		{
//			throw out_of_range("Cannot create such an old owner: " + to_string(new_age));
//		}
//		name = new_name;
//		surname = new_surname;
//		age = new_age;
//	}
//
//	string GetName () const
//	{
//		return name;
//	}
//	string GetSurname() const
//	{
//		return surname;
//	}
//
//	int GetAge() const
//	{
//		return age;
//	}
//
//private:
//	string name;
//	string surname;
//	int age;
//};
//
//class Database
//{
//public:
//
//private:
//	map<Owner, map<Company, set<CarModel>>> CarsInGarage;
//};
//
//ostream& operator << (ostream& stream, const Owner& owner )
//{
//	stream << owner.GetName() << ' ' << owner.GetSurname() << ", "
//		<< owner.GetAge() << " years old";
//	return stream;
//}



class CarModel
{
public:
	CarModel(const string& new_name, const string& new_type, const  int& new_powerValue)
	{
		if (new_name.size() > 12 || new_name.empty())
		{
			throw out_of_range("Model name is incorrect: " + new_name);
		}
		else if (new_type.size() > 8 || new_type.empty())
		{
			throw out_of_range("Type name is incorrect " + new_type);
		}
		else if (new_powerValue > 2500 || new_powerValue < 250)
		{
			throw out_of_range("Powe Value is incorrect " + to_string(new_powerValue));
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

class Database
{
public:

	void AddCompanyModel(const string& company, const CarModel& carmodel)
	{
		database[company].insert(carmodel);
	}

	int CheckString(const string& sinput) const
	{
		for (const auto& k : database)
		{
			if (k.first == sinput)
			{
				return 1;
			}
			else
			{
				for (const auto& i : k.second)
				{
					if (i.GetCarType() == sinput)
					{
						return 2;
					}
					else if (i.GetCarModelName() == sinput)
					{
						return 3;
					}
				}
			}
		}

		return 4;

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
			unsigned int s = 0;
			for (const auto& k : i.second)
			{
				++s;
				if (s < i.second.size())
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
				if (k.first == companyname)
				{
					unsigned int s = 0;
					for (const auto& i : k.second)
					{

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

	void PrintType(const string& sinput) const
	{
		vector <string> typebase;
		for (const auto& k : database)
		{
			for (const auto& i : k.second)
			{
				if (i.GetCarType() == sinput)
				{

					typebase.push_back(i.GetCarModelName());

				}
			}
		}

		cout << sinput << ": ";
		unsigned int x = 0;
		for (const auto& s : typebase)
		{
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
					cout << i.GetCarModelName() << " made by" << k.first << " with " << i.GetCarType() << " type " << " and " << i.GetCarPowerValue() << "hp" << endl;
				}
			}
		}
	}

	bool DeleteCompany(const string& _companyname)
	{
		for (const auto& k : database)
		{
			if (k.first == _companyname)
			{
				database.erase(_companyname);
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	int DeleteCarMOdel(const string& _companyname, const string& _carmodel)
	{
		for (const auto& k : database)
		{
			if (k.first == _companyname)
			{
				for (const auto& i : k.second)
				{
					if (i.GetCarModelName() == _carmodel)
					{
						set<CarModel>::iterator it = k.second.find(i.GetCarModelName());
					}

				}
			}
		}
	}
private:
	map<string, set<CarModel>> database;
};




//void ValidNextCharAndSkip (stringstream& s, const string& carmodel) 
//{
//	if (s.peek() != ' ')
//	{
//		throw logic_error("Wrong format in: " + carmodel);
//	}
//	s.ignore(1);
//}

CarModel ParseCarModel(const string& carmodel, const string& cartype, const int& powerValue)
{
	stringstream car_stream(carmodel);
	stringstream car_type(cartype);
	string name, type;
	car_stream >> name;
	// ValidNextCharAndSkip(car_stream, carmodel);
	car_type >> type;
	// ValidNextCharAndSkip(car_stream, carmodel);
	return { name, type, powerValue };

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
				string _companyname, _carName, _carType;
				int _carPowerValue;

				stream >> _companyname >> _carName >> _carType >> _carPowerValue;

				const CarModel car = ParseCarModel(_carName, _carType, _carPowerValue);

				base.AddCompanyModel(_companyname, car);

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
					if (base.CheckString(sinput) == 1)
					{
						base.PrintCompany(sinput);
					}
					else if (base.CheckString(sinput) == 2)
					{
						base.PrintType(sinput);
					}
					else if (base.CheckString(sinput) == 3)
					{
						base.PrintCarInformation(sinput);
					}
					else if (base.CheckString(sinput) == 4)
					{
						cout << "No such a type or a company in database: " + sinput << endl;
					}
				}

			}
			else if (operation == "Del")
			{
				string _companyname, _carname;
				stream >> _companyname;

				if (!stream.eof())
				{
					stream >> _carname;
				}

				if (_carname.empty())
				{
					if (base.DeleteCompany(_companyname))
					{
						cout << _companyname << " was deleted successfully" << endl;
					}
					else
					{
						cout << "Company named " << _companyname << " not found" << endl;
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