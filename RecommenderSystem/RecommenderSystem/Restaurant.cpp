#include "Restaurant.h"
#include <fstream>


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
