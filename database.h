#pragma once

#include "car_model.h"
#include "what_found.h"

#include <iostream>
#include <vector>
#include <map>
#include <set>

class Database
{
public:

	void AddModel(const string& company, const CarModel& carmodel);
	void AddCompany(const string& company);
	void PrintAllModels() const;
	void PrintCompany(const string& companyname) const;
	void PrintType(const string& type) const;
	void PrintCarInformation(const string& sinput) const;

	unsigned int DeleteCompany(const string& companyname);
	bool DeleteCarModel(const string& _companyname, const string& _carmodel); // Returns true if it is successful to delete a car, else return false;
	unsigned int DeleteAll(const string& string);

	WhatFound CheckStringToPrint(const string& sinput) const;
	uint16_t CheckStringToChangeCompany(const string& sourcename, const string& newcompanyname) const;
	uint16_t CheckStringToChangeCar(const string& companyname, const string& oldcarname, const string& newcarname) const;
	WhatFound ChangeCarInCompany(const string& companyname, const string& oldcarname, const string& newcarname);

	WhatFound ChangeCompany(const string& name, const string& newname);

private:
	map<string, set<CarModel, less<>>> database;
};