// Add - Add a new company with a car (name, type, powervalue);
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
#include <cctype>

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

bool operator<(const string& lhs, const CarModel& rhs)
{
	return lhs < rhs.GetCarModelName();
}

bool operator<(const CarModel& lhs, const string& rhs)
{
	return lhs.GetCarModelName() < rhs;
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
				if (k.second.empty())
				{
					cout << companyname << " hasn't any cars" << endl;
				}
				else if (k.first == companyname)
				{
					unsigned int s = 0;
					cout << companyname << ": ";
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

	unsigned int DeleteCompany(const string& _companyname)
	{
		if (database.find(_companyname) != database.end())
		{
			unsigned int deletedCars = database[_companyname].size();
			database.erase(_companyname);
			return deletedCars;
		}
		else
		{
			return 0;
		}
	}

	bool DeleteCarModel(const string& _companyname, const string& _carmodel)
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
		if (isalpha(k) == 0)
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
	
	return { name, type, powerValue };
}

string ParseCompanyName (const string& _companyname)
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
				string _companyname, _carName, _carType;
				int _carPowerValue;

				stream >> _companyname >> _carName >> _carType >> _carPowerValue;

				const string companyname = ParseCompanyName(_companyname);
				const CarModel car = ParseCarModel(_carName, _carType, _carPowerValue);

				base.AddCompanyModel(companyname, car);

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

				const string companyname = ParseCompanyName(_companyname);
				
				if (!stream.eof())
				{
					stream >> _carname;
				}

				if (_carname.empty())
				{
					const int deletedCars = base.DeleteCompany(companyname);
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