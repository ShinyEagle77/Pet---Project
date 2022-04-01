#include "car_model.h"


string CarModel::GetCarModelName() const
{
	return name;
}
string CarModel::GetCarType() const
{
	return type;
}
int CarModel::GetCarPowerValue() const
{
	return powerValue;
}

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
