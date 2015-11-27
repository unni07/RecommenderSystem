#include "precompiled.h"
#include "Restaurant.h"
#include "Features.h"
#include <fstream>

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

		//const_cast<Feature *>(feature)->AddRestaurant(*this);

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


float Restaurant::ComputeDistance(const Restaurant &rhs) const
{
	float distance = 0;

	if (rhs.decor_quality_ < decor_quality_)
		distance += decor_quality_ - rhs.decor_quality_;

	if (rhs.food_quality_ < food_quality_)
		distance += food_quality_ - rhs.food_quality_;

	if (rhs.price_range_ > price_range_)
		distance += rhs.price_range_ - price_range_;

	if (rhs.service_quality_ < service_quality_)
		distance += service_quality_ - rhs.service_quality_;

	unsigned checked = 0;
	for (unsigned feature : features_)
	{
		auto found = std::find(rhs.features_.begin(), rhs.features_.end(), feature);

		if (found == rhs.features_.end())
			distance += 1.0f;
		else
			checked++;
	}

	if (checked < rhs.features_.size())
		distance += 0.1f * (rhs.features_.size() - checked);

	return distance;
}
