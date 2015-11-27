#include "precompiled.h"
#include "Features.h"
#include <fstream>

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

const std::vector<const Restaurant *> FeatureDatabase::GetListOfRestaurantsByKeyword(const std::string &feature_name)
{
	if (features_.find(feature_name) == features_.end())
		return std::vector<const Restaurant *>();

	return features_[feature_name].restaurants_;
}
