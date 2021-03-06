#include "precompiled.h"
#include "Features.h"
//#include <fstream>
//#include <set>
#include "Restaurant.h"
#include "City.h"

std::vector<std::string>		FeatureDatabase::feature_name_list_;
std::map<std::string, Feature>	FeatureDatabase::features_;

void FeatureDatabase::Initialize()
{
	ReadFeatures();
}

void FeatureDatabase::ReadFeatures()
{
	std::ifstream is("Database/features.txt");

	std::string line;
	while (!is.eof())
	{
		std::getline(is, line);

		unsigned feature_start = line.find_first_of('\t');

		unsigned ID		 = std::atoi(line.substr(0, feature_start).c_str());
		std::string name = line.substr(feature_start+1);
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		Feature feat;
		feat.name_ = name;
		feat.ID_ = ID;
		if (ID >= 50 && ID <= 56)
			feat.type_ = Feature::enDecorQuality;
		else if (ID >= 73 && ID <= 78)
			feat.type_ = Feature::enFoodQuality;
		else if (ID >= 161 && ID <= 170)
			feat.type_ = Feature::enPriceRange;
		else if (ID >= 203 && ID <= 208)
			feat.type_ = Feature::enServiceQuality;
		else
			feat.type_ = Feature::enGeneric;

		feature_name_list_.push_back(name);
		features_[name] = feat;
	}
}


const Feature *FeatureDatabase::Get(unsigned ID)
{
	if (ID > 256)
		return nullptr;

	return &features_[feature_name_list_[ID]];
}

const Feature *FeatureDatabase::Get(const std::string &name)
{
	if (features_.find(name) == features_.end())
		return nullptr;

	return &features_[name];
}


const std::vector<std::string> FeatureDatabase::GetListOfRestaurantNamesByKeyword(const std::string &feature_name)
{
	if (features_.find(feature_name) == features_.end())
		return std::vector<std::string>();

	return features_[feature_name].restaurants_;
}

/*const std::vector<const Restaurant *> FeatureDatabase::GetListOfRestaurantsByKeyword(const std::string &feature_name)
{
	if (features_.find(feature_name) == features_.end())
		return std::vector<const Restaurant *>();

	return features_[feature_name].restaurants_;
}


const std::vector<std::string> FeatureDatabase::GetListOfRestaurantNamesByKeyword(const std::string &feature_name, const std::vector<std::string> &cities)
{
	if (features_.find(feature_name) == features_.end())
		return std::vector<std::string>();

	std::vector<std::string> restaurants;

	for (auto res : features_[feature_name].restaurants_)
	{
		auto found = std::find(cities.begin(), cities.end(), res->city());
		if (found != cities.end())
			restaurants.push_back(res);
	}

	return restaurants;
}*/


const std::vector<std::string> FeatureDatabase::GetListOfRestaurantNamesByKeywordList(const std::vector<std::string> &feature_name_list)
{
	std::vector<std::vector<std::string>> list_of_restaurants;

	for (auto feature_name : feature_name_list)
	{
		if (features_.find(feature_name) == features_.end())
			continue;

		list_of_restaurants.push_back(features_[feature_name].restaurants_);
	}

	auto it1 = list_of_restaurants.begin();
	auto it2 = list_of_restaurants.begin(); it2++;
	std::vector<std::string> dest;

	intersection(*it1, *it2, dest);

	auto end = list_of_restaurants.end();
	for (; it2 != end; it2++)
	{
		std::vector<std::string> temp = dest;

		intersection(temp, *it2, dest);
	}

	return dest;
}

/*const std::vector<const Restaurant *> FeatureDatabase::GetListOfRestaurantsByKeywordList(const std::vector<std::string> &feature_name_list)
{
	std::vector<std::vector<const Restaurant *>> list_of_restaurants;

	for (auto feature_name : feature_name_list)
	{
		if (features_.find(feature_name) == features_.end())
			continue;

		list_of_restaurants.push_back(features_[feature_name].restaurants_);
	}

	auto it1 = list_of_restaurants.begin();
	auto it2 = list_of_restaurants.begin(); it2++;
	std::vector<const Restaurant *> dest;

	intersection(*it1, *it2, dest);

	auto end = list_of_restaurants.end();
	for (; it2 != end; it2++)
	{
		std::vector<const Restaurant *> temp = dest;

		intersection(temp, *it2, dest);
	}

	return dest;
}

const std::vector<const Restaurant *> FeatureDatabase::GetListOfRestaurantsByKeywordList(const std::vector<std::string> &feature_name_list, const std::vector<std::string> &cities)
{
	std::vector<std::vector<const Restaurant *>> list_of_restaurants;

	for (auto feature_name : feature_name_list)
	{
		if (features_.find(feature_name) == features_.end())
			continue;

		std::vector<const Restaurant *> restaurants;

		for (auto res : features_[feature_name].restaurants_)
		{
			auto found = std::find(cities.begin(), cities.end(), res->city());
			if (found != cities.end())
				restaurants.push_back(res);
		}

		list_of_restaurants.push_back(restaurants);
	}

	auto it1 = list_of_restaurants.begin();
	auto it2 = list_of_restaurants.begin(); it2++;
	std::vector<const Restaurant *> dest;

	intersection(*it1, *it2, dest);

	auto end = list_of_restaurants.end();
	for (; it2 != end; it2++)
	{
		std::vector<const Restaurant *> temp = dest;

		intersection(temp, *it2, dest);
	}

	return dest;
}
*/

std::vector<std::string> FeatureDatabase::GetClosestRestaurants(const std::vector<std::string> &feature_name_list)
{
	std::set<std::string> list_of_restaurants;

	for (auto feature_name : feature_name_list)
	{
		if (features_.find(feature_name) == features_.end())
			continue;

		for (auto restaurant : features_[feature_name].restaurants_)
		{
			list_of_restaurants.insert(restaurant);
		}
	}


	float best_dist = std::numeric_limits<float>::max();
	float second_dist = std::numeric_limits<float>::max();
	float third_dist = std::numeric_limits<float>::max();
	std::string best_rest;
	std::string second_best;
	std::string third_best;

	for (auto restaurant : list_of_restaurants)
	{
		float dist = CityDatabase::GetRestaurant(restaurant).ComputeDistance(feature_name_list);

		if (dist < third_dist)
		{
			if (dist < second_dist)
			{
				if (dist < best_dist)
				{
					third_dist = second_dist;
					second_dist = best_dist;
					best_dist = dist;

					third_best = second_best;
					second_best = best_rest;
					best_rest = restaurant;
				}
				else
				{
					third_dist = second_dist;
					second_dist = dist;

					third_best = second_best; 
					second_best = restaurant;
				}
			}
			else
			{
				third_dist = dist;
				third_best = restaurant;
			}
		}
	}

	std::vector<std::string> restaurants;
	restaurants.push_back(best_rest);
	restaurants.push_back(second_best);
	restaurants.push_back(third_best);

	return restaurants;
}

/*std::vector<const Restaurant *> FeatureDatabase::GetClosestRestaurants(const std::vector<std::string> &feature_name_list, const std::vector<std::string> &cities)
{
	std::set<const Restaurant *> list_of_restaurants;

	for (auto feature_name : feature_name_list)
	{
		if (features_.find(feature_name) == features_.end())
			continue;

		for (auto restaurant : features_[feature_name].restaurants_)
		{
			auto found = std::find(cities.begin(), cities.end(), restaurant->city());
			if (found != cities.end())
				list_of_restaurants.insert(restaurant);
		}
	}


	float best_dist = std::numeric_limits<float>::max();
	const Restaurant *best_rest = nullptr;
	const Restaurant *second_best = nullptr;
	const Restaurant *third_best = nullptr;

	for (auto restaurant : list_of_restaurants)
	{
		float dist = restaurant->ComputeDistance(feature_name_list);

		if (dist < best_dist)
		{
			best_dist = dist;
			third_best = second_best;
			second_best = best_rest;
			best_rest = restaurant;

		}
	}
	std::vector<const Restaurant *> restaurants;
	restaurants.push_back(best_rest);
	restaurants.push_back(second_best);
	restaurants.push_back(third_best);
	return restaurants;
}
*/


void FeatureDatabase::intersection(const std::vector<std::string> &set1, const std::vector<std::string> &set2, std::vector<std::string> &result)
{
	for (auto it1 : set1)
	{
		if (std::find(set2.begin(), set2.end(), it1) != set2.end())
		{
			result.push_back(it1);
		}
	}
}
