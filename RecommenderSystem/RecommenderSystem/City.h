#pragma once

#include "Restaurant.h"



struct City
{
public:
	City() {}
	City(const std::string &name);

	std::string name_;
	std::vector<Restaurant> restaurants_;

	Restaurant FindBestMatch(const Restaurant &res);

	enum enCities
	{
		atlanta,
		boston,
		chicago,
		los_angeles,
		new_orleans,
		new_york,
		san_francisco,
		washington_dc
	};
};


class CityDatabase
{
public:
	static void Initialize();

private:
	static void ReadCities();
	static std::map<City::enCities, City> cities_;
};
