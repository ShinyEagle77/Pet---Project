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

// WHILE INPUT() CATCH EXCEPTIONS
// WRITE TEST
// OPTIMIZE METHODS AND BASES
// POSSIBLE REWORK BASE CONTAINER
// Print doesn't working correctly after Change "companyname" "oldcarname" "newcarname"

#include "test_runner.h"
#include "profile.h"

#include "what_found.h"
#include "car_model.h"
#include "database.h"
#include "parse_funcs.h"


#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <iomanip>
#include <sstream>

#include "programm_descrip.h"

using namespace std;

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
							const string& _oldcarname = _newcompanyname; // Variable name changed for better readability
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
			else if (operation == "help")
			{
				PrintDescription();
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
