
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

// Add enum class for a return value;

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

	void SetCarModelName(const string& newname)
	{
		name = newname;
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
			uint16_t s = 0;
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
					uint16_t s = 0;
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
		uint16_t x = 0;
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
					cout << i.GetCarModelName() << " made by " << k.first << " with " << i.GetCarType() << " type" << " and " << i.GetCarPowerValue() << "hp" << endl;
				}
			}
		}
	}

	unsigned int DeleteCompany(const string& _companyname)
	{
		if (database.find(_companyname) != database.end())
		{
			const unsigned int deletedCars = database[_companyname].size();
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

	unsigned int DeleteAll(const string& string)
	{
		const unsigned int count = database.size();

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

	uint16_t CheckStringToPrint(const string& sinput)
	{
		uint16_t CheckResult = 4;
		for (const auto& k : database)
		{
			if (k.first == sinput)
			{
				CheckResult = 1;
				return CheckResult;
			}
			else
			{
				for (const auto& i : k.second)
				{
					if (i.GetCarType() == sinput)
					{
						CheckResult = 2;
						return CheckResult;
					}
					else if (i.GetCarModelName() == sinput)
					{
						CheckResult = 3;
						return CheckResult;
					}
				}
			}
		}
		return CheckResult;
	}

	uint16_t CheckStringToChangeCompany(const string& sourcename, const string& newcompanyname)
	{
		uint16_t result = 0;

		if (database.find(sourcename) != database.end())
		{
			result = 1;  // Company NAME found;
		}
		if (database.find(sourcename) != database.end() && database.find(newcompanyname) != database.end())
		{
			result = 2; // Companies NAME and NEWNAME found;
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
					result = 1;
				}
				if (k.second.find(oldcarname) != k.second.end() && k.second.find(newcarname) != k.second.end())
				{
					result = 2;
				}
			}
		}

		return result;
		
	}

	unsigned int ChangeCarInCompany (const string& companyname, const string& oldcarname, const string& newcarname)
	{
		const uint16_t result = CheckStringToChangeCar(companyname, oldcarname, newcarname);
		if (result == 0)
		{
			return 0;
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
							CarModel newCar{ newcarname, i.GetCarType(), i.GetCarPowerValue() };
							database[companyname].insert(newCar);
							if (DeleteCarModel(companyname, oldcarname))
							{
								return 1;
							}
						}
					}
				}
			}
			
		}
		else if (result == 2)
		{
			return 2;
		}

		return 0;
	}

	uint16_t ChangeCompany(const string& name, const string& newname)
	{
		
		const uint16_t result = CheckStringToChangeCompany(name, newname);
		if (result == 0)
		{
			return 0;
		}
		else if (result == 1)
		{

			auto node = database.extract(name);
			node.key() = newname;
			database.insert(move(node));

			database.erase(name);
			return 1;
		}
		else if (result == 2)
		{
			return 2;
		}

		return 0;
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
				if (stream.eof())
				{
					if (_companyname.empty())
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
					const uint16_t result = base.CheckStringToPrint(sinput);
					if (result == 1)
					{
						base.PrintCompany(sinput);
					}
					else if (result == 2)
					{
						base.PrintType(sinput);
					}
					else if (result == 3)
					{
						base.PrintCarInformation(sinput);
					}
					else if (result == 4)
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
						cout << "Write as a second argument a NEW companyname" << endl;
					}
					else if (_newcarname.empty())
					{
						const string newcompanyname = ParseCompanyName(_newcompanyname);

						const unsigned int result = base.ChangeCompany(_companyname, _newcompanyname);

						if (result == 0)
						{
							cout << "Company named " << _companyname << " not found" << endl;
						}
						else if (result == 1)
						{
							cout << "Company named " << _companyname << " changed her name to " << _newcompanyname << endl;
						}
						else if (result == 2)
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
							const string _oldcarname = _newcompanyname;
							const unsigned int result = base.ChangeCarInCompany(_companyname, _oldcarname, _newcarname);
							
							if (result == 0)
							{
								cout << "Car name " << _oldcarname << " not found" << endl;
							}
							else if (result == 1)
							{
								
								cout << "Car named " << _oldcarname << " changed name to " << _newcarname << endl;
							}
							else if (result == 2)
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
