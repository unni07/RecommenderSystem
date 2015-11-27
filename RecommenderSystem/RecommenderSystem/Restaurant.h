#pragma once

#include <vector>
#include <string>

//#include "Features.h"


#define NO_FEATURE 0xFFFFFFFF

class Restaurant
{
public:
	Restaurant() :
		decor_quality_(NO_FEATURE),
		food_quality_(NO_FEATURE),
		price_range_(NO_FEATURE),
		service_quality_(NO_FEATURE)
		{}

	Restaurant(const std::string &line, const std::string &city);

	void setName(const std::string &name) { name_ = name; }
	void setCity(const std::string &city) { city_ = city; }
	void setDecorQuality(unsigned decor);
	void setFoodQuality(unsigned food);
	void setPriceRange(unsigned price);
	void setServiceQuality(unsigned service);
	void AddFeature(unsigned feat) { features_.push_back(feat); }

	void RegisterFeatures();

	float ComputeDistance(const Restaurant &rhs) const;

private:
	std::string name_;
	std::string city_;

	std::vector<unsigned> features_;
	unsigned	decor_quality_;
	unsigned	food_quality_;
	unsigned	price_range_;
	unsigned	service_quality_;
};

