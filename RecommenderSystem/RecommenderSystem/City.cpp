#include "City.h"
#include <fstream>


City::City(const std::string &name) : name_(name)
{
	std::ifstream is(name + ".txt");

	std::string line;
	while (!is.eof())
	{
		std::getline(is, line);

		unsigned name_start = line.find_first_of('\t') + 1;

		unsigned name_end = line.find_last_of('\t');

		Restaurant new_restaurant;

		std::string name = line.substr(name_start, name_end - name_start);
		new_restaurant.name_ = name;

		std::string features = line.substr(name_end+1);

		unsigned digit_start = 0;
		while (digit_start < features.size())
		{
			unsigned feature_ID = std::atoi(features.substr(digit_start, 3).c_str());

			const Feature *feature = FeatureDatabase::Get(feature_ID);

			switch (feature->type_)
			{
			case Feature::enDecorQuality:
				new_restaurant.decor_quality_ = feature_ID;
				break;

			case Feature::enFoodQuality:
				new_restaurant.food_quality_ = feature_ID;
				break;

			case Feature::enPriceRange:
				new_restaurant.price_range_ = feature_ID;
				break;

			case Feature::enServiceQuality:
				new_restaurant.service_quality_ = feature_ID;
				break;

			default:
				new_restaurant.features_.push_back(feature_ID);
				break;
			}


			digit_start += 4;
		}

		restaurants_.push_back(new_restaurant);
	}
}

Restaurant City::FindBestMatch(const Restaurant &match)
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
}



std::map<City::enCities, City> CityDatabase::cities_;

void CityDatabase::Initialize()
{
	ReadCities();

	Restaurant resu;
	resu.setName("resu");
	resu.setDecorQuality(52);
	resu.setFoodQuality(74);
	resu.setPriceRange(164);
	resu.setServiceQuality(204);

	resu.features_.push_back(253);
	resu.features_.push_back(192);
	resu.features_.push_back(174);
	resu.features_.push_back(250);
	resu.features_.push_back(200);
	resu.features_.push_back(063);
	resu.features_.push_back(197);
	resu.features_.push_back(142);

	cities_[City::new_york].FindBestMatch(resu);
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