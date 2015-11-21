#pragma once

#include <vector>
#include <string>


/*enum enDecorQuality
{
	Poor,
	Fair,
	Good,
	Excellent,
	Extraordinary,
	Near_perfect
};

enum enFoodQuality
{
	Fair,
	Good,
	Excellent,
	Extraordinary,
	Near_perfect
};

enum enPriceRange
{
	Below_fifteen,
	Between_fifteen_and_thirty,
	Between_thirty_and_fifty,
	Over_fifty
};

enum enServiceQuality
{
	Fair,
	Good,
	Excellent,
	Extraordinary,
	Near_perfect
};
*/
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
};

class FeatureDatabase
{

public:
	static void Initialize();
	static void Terminate();

	static const Feature *Get(unsigned ID);

private:
	static void ReadFeatures();
	static std::vector<Feature> features_;
};
