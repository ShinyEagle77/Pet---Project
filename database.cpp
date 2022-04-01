#include "database.h"

void Database::AddModel(const string& company, const CarModel& carmodel)
{
	database[company].insert(carmodel);
}

void Database::AddCompany(const string& company)
{
	database[company];
}

void Database::PrintAllModels() const
{
	if (database.empty())
	{
		cout << "No models in database" << endl;
	}
	for (const auto& [company, cars] : database)
	{
		cout << company << ": ";
		for (const auto& k : cars)
		{
			static uint16_t s = 0;
			++s;
			if (s < cars.size())		// If there are several models in a row, adds ',' between them for a better printing. (Bayonetta, Aventador, California)
			{
				cout << k.GetCarModelName() << ", ";
			}
			else if (s == cars.size())
			{
				cout << k.GetCarModelName();
			}

		}
		cout << endl;
	}
}

void Database::PrintCompany(const string& companyname) const
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

void Database::PrintType(const string& type) const
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

void Database::PrintCarInformation(const string& sinput) const
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

unsigned int Database::DeleteCompany(const string& companyname)
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

bool Database::DeleteCarModel(const string& _companyname, const string& _carmodel) // Returns true if it is successful to delete a car, else return false;
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

unsigned int Database::DeleteAll(const string& string)
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

WhatFound Database::CheckStringToPrint(const string& sinput) const
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

uint16_t Database::CheckStringToChangeCompany(const string& sourcename, const string& newcompanyname) const
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

uint16_t Database::CheckStringToChangeCar(const string& companyname, const string& oldcarname, const string& newcarname) const
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

WhatFound Database::ChangeCarInCompany(const string& companyname, const string& oldcarname, const string& newcarname)
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

WhatFound Database::ChangeCompany(const string& name, const string& newname)
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
