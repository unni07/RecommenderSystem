#pragma once

class Restaurant; 


struct Feature
{
	/// This enum differentiates between generic features and special cases
	enum enType
	{
		enGeneric,
		enDecorQuality,
		enFoodQuality,
		enPriceRange,
		enServiceQuality
	} type_;

	/// Name and ID of the feature
	std::string name_;
	unsigned ID_;
	/// List oif restaurants where this feature is featured
	std::vector<const Restaurant *> restaurants_;

	/// Used for keeping track of which restaurants contain this feature
	void AddRestaurant(const Restaurant *res) { restaurants_.push_back(res); };
};


class FeatureDatabase
{
public:
	/// Call once in main
	static void Initialize();

	/// Returns a list with all the feature names
	static const std::vector<std::string> GetFeatureNameList() { return feature_name_list_; }

	/// Get a specific feature by ID
	static const Feature *Get(unsigned ID);
	/// Get a specific feature by name
	static const Feature *Get(const std::string &name);

	/// Pass a feature name and get the list of restaurants asociated to that feature
	static const std::vector<const Restaurant *> GetListOfRestaurantsByKeyword(const std::string &feature_name);
	static const std::vector<const Restaurant *> GetListOfRestaurantsByKeyword(const std::string &feature_name, const std::vector<std::string> &cities);
	/// Pass a feature name list and get the list of restaurants asociated to all of those features
	static const std::vector<const Restaurant *> GetListOfRestaurantsByKeywordList(const std::vector<std::string> &feature_name_list);
	static const std::vector<const Restaurant *> GetListOfRestaurantsByKeywordList(const std::vector<std::string> &feature_name_list, const std::vector<std::string> &cities);
	/// Pass a feature name list and get a list of restaurants that are close enough to this features
	std::vector<const Restaurant *> GetClosestRestaurants(const std::vector<std::string> &feature_name_list);
	std::vector<const Restaurant *> GetClosestRestaurants(const std::vector<std::string> &feature_name_list, const std::vector<std::string> &cities);


private:
	static void ReadFeatures();
	static std::vector<std::string> feature_name_list_;
	static std::map<std::string, Feature> features_;
	static void intersection(const std::vector<const Restaurant *> &, const std::vector<const Restaurant *> &, std::vector<const Restaurant *> &);
};
