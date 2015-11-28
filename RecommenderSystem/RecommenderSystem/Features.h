#pragma once

//#include "Restaurant.h"

class Restaurant;


struct Feature
{
	enum enType
	{
		enGeneric,
		enDecorQuality,
		enFoodQuality,
		enPriceRange,
		enServiceQuality
	} type_;

	std::string name_;

	unsigned ID_;

	void AddRestaurant(const Restaurant *res) { restaurants_.push_back(res); }

	std::vector<const Restaurant *> restaurants_;
};

class FeatureDatabase
{

public:
	static void Initialize();
	//static void Terminate();

	static const std::vector<std::string> GetFeatureNameList() { return feature_name_list_; }

	static const Feature *Get(unsigned ID);
	static const std::vector<const Restaurant *> GetListOfRestaurantsByKeyword(const std::string &feature_name);
	static const std::vector<const Restaurant *> GetListOfRestaurantsByKeywordList(const std::vector<std::string> &feature_name_list);

private:
	static void ReadFeatures();
	static std::vector<std::string> feature_name_list_;
	static std::map<std::string, Feature> features_;
};
