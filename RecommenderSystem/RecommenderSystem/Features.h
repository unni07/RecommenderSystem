#pragma once


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

	std::vector<Restaurant *> restaurants_;
};

class FeatureDatabase
{

public:
	static void Initialize();
	//static void Terminate();

	static std::vector<Restaurant> GetListOfRestaurentsByKeyword(const std::string &feature_name); // everything to lowercase!!
	static std::vector<Restaurant> GetListOfRestaurentsByFeature(const Feature &features);

private:
	static void ReadFeatures();
	static std::map<std::string, Feature> features_;
};
