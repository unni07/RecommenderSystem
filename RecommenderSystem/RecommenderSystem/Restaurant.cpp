#include "precompiled.h"
#include "Restaurant.h"
#include "Features.h"


Restaurant::Restaurant(const std::string &line, const std::string &city)
{
	setCity(city);

	unsigned name_start = line.find_first_of('\t') + 1;
	unsigned name_end = line.find_last_of('\t');

	std::string name = line.substr(name_start, name_end - name_start);
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	name_ = name;

	std::string features = line.substr(name_end + 1);

	unsigned digit_start = 0;
	while (digit_start < features.size())
	{
		unsigned feature_ID = std::atoi(features.substr(digit_start, 3).c_str());

		const Feature *feature = FeatureDatabase::Get(feature_ID);

		switch (feature->type_)
		{
		case Feature::enDecorQuality:
			setDecorQuality(feature_ID);
			break;

		case Feature::enFoodQuality:
			setFoodQuality(feature_ID);
			break;

		case Feature::enPriceRange:
			setPriceRange(feature_ID);
			break;

		case Feature::enServiceQuality:
			setServiceQuality(feature_ID);
			break;

		default:
			features_.push_back(feature_ID);
			break;
		}

		digit_start += 4;
	}
}

void Restaurant::setDecorQuality(unsigned decor)
{
	if (decor == 56)
		decor = 52;

	decor_quality_ = decor;
}

void Restaurant::setFoodQuality(unsigned food)
{
	if (food == 78)
		food = 74;

	food_quality_ = food;
}

void Restaurant::setPriceRange(unsigned price)
{
	if (price == 162 || price == 163)
		price = 161;

	else if (price == 165 || price == 166 || price == 170)
		price = 164;

	else if (price == 168)
		price = 167;

	price_range_ = price;
}

void Restaurant::setServiceQuality(unsigned service)
{
	if (service == 208)
		service = 204;

	service_quality_ = service;
}

void Restaurant::RegisterFeatures()
{
	for (auto feat : features_)
	{
		const Feature *feature = FeatureDatabase::Get(feat);

		const_cast<Feature *>(feature)->AddRestaurant(this);
	}
}


float Restaurant::ComputeDistance(const std::vector<std::string> &feature_list) const
{
	float distance = 0;
	unsigned checked = 0;

	for (auto feature_name : feature_list)
	{
		const Feature *feature = FeatureDatabase::Get(feature_name);

		switch (feature->type_)
		{
		case Feature::enDecorQuality:
			if (decor_quality_ < feature->ID_)
				distance += feature->ID_ - decor_quality_;
			checked++;
			break;

		case Feature::enFoodQuality:
			if (food_quality_  < feature->ID_)
				distance += feature->ID_ - food_quality_;
			checked++;
			break;

		case Feature::enPriceRange:
			if (service_quality_ > feature->ID_)
				distance += service_quality_ - feature->ID_;
			checked++;
			break;

		case Feature::enServiceQuality:
			if (food_quality_ < feature->ID_)
				distance += feature->ID_ - food_quality_;
			checked++;
			break;

		case Feature::enGeneric:
			auto found = std::find(features_.begin(), features_.end(), (*feature).ID_);

			if (found == features_.end())
				distance += 1.0f;
			else
				checked++;

			break;
		};


		if (checked < features_.size())
			distance += 0.1f * (features_.size() - checked);
	}

	return distance;
}

//std::string Restaurant::getNameOfRestaurant() const
//{
//	return name_;
//}
