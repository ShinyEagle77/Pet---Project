// ADD, PRINT, FIND, DEL

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <exception>
#include <set>
#include <iomanip>
#include <sstream>
#include <fstream>

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
	CarModel (const string& new_name, const string& new_type, const  int& new_powerValue)
	{
		if (new_name.size() > 15 || new_name.empty())
		{
			throw out_of_range("Model name is incorrect: " + new_name);
		}
		else if (new_type.size () > 12 || new_type.empty())
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

	string GetCarModelName () const
	{
		return name;
	}
	string GetCarType () const
	{
		return type;
	}
	int GetCarPowerValue () const
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

	void AddCompanyModel (const string& company, const CarModel& carmodel)
	{
		database[company].insert(carmodel);
	}

	void PrintCompanyModels() const
	{
		for (const auto& i : database)
		{
			for (const auto& k : i.second)
			{
				cout << i.first << ": " << k.GetCarModelName() << ' ';
			}
			cout << endl;
		}
	}

private:
	map<string, set<CarModel>> database;
};


void ValidNextCharAndSkip (stringstream& s, const string& carmodel) // NEEDS TO REWORK
{
	if (s.peek() != ' ')
	{
		throw logic_error("Wrong format in: " + carmodel);
	}
	s.ignore(1);
}

CarModel ParseCarModel (const string& carmodel, const int& powerValue) // REWORK!!!
{
	stringstream car_stream(carmodel);
	string name, type;
	car_stream >> name;
	ValidNextCharAndSkip(car_stream, carmodel);
	car_stream >> type;
	ValidNextCharAndSkip(car_stream, carmodel);
	if (!car_stream.eof() || !car_stream)
	{
		throw logic_error("Wrong format : " + carmodel);
	}
	
	return { name, type, powerValue };
	
}

int main()
{
	try
	{
		Database base;
		string command;
		while(getline(cin,command))
		{
			stringstream stream(command);

			string operation;
			stream >> operation;

			if (operation == "Add")
			{
				string _companyname, _carName, _carType;
				int _carPowerValue;

				stream >> _companyname >> _carName >> _carType >> _carPowerValue; // REWORK THIS SHIT

				const CarModel car = ParseCarModel(_carName, _carPowerValue);
				
				
				base.AddCompanyModel(_companyname, car);
				
			}
			else if (operation == "Print")
			{
				base.PrintCompanyModels();
			}
			else if (!operation.empty())
			{
				throw logic_error("Unknown command " + command);
			}
		}
	} catch (exception& ex) {

		cout << ex.what() << endl;
	}

	return 0;
	
}