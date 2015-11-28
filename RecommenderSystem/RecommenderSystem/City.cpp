#include "precompiled.h"
#include "City.h"



City::City(const std::string &name) : name_(name)
{
	std::ifstream is("Database/" + name + ".txt");

	std::string line;
	while (!is.eof())
	{
		std::getline(is, line);

		Restaurant new_restaurant(line, name_);

		restaurants_.push_back(new_restaurant);
		restaurants_.back().RegisterFeatures();
	}
}

/*Restaurant City::FindBestMatch(const Restaurant &match)
{
	float best_dist = std::numeric_limits<float>::max();
	Restaurant best_rest;

	for (auto restaurant : restaurants_)
	{
		float dist = match.ComputeDistance(restaurant);

		if (dist < best_dist)
		{
			best_dist = dist;
			best_rest = restaurant;
		}
	}

	return best_rest;
}*/



std::map<City::enCities, City> CityDatabase::cities_;

void CityDatabase::Initialize()
{
	ReadCities();
}

void CityDatabase::ReadCities()
{
	cities_[City::atlanta]			= City("atlanta");
	cities_[City::boston]			= City("boston");
	cities_[City::chicago]			= City("chicago");
	cities_[City::los_angeles]		= City("los_angeles");
	cities_[City::new_orleans]		= City("new_orleans");
	cities_[City::new_york]			= City("new_york");
	cities_[City::san_francisco]	= City("san_francisco");
	cities_[City::washington_dc]	= City("washington_dc");
}