#pragma once
class KeyWordSearch
{
public:
	static KeyWordSearch& getInstance();
	
	void initialize();
	std::vector<std::string> search(std::string name);
	/*get recommendation with respect to choices*/
	//void recommendation(std::map<std::string, std::vector<std::string>> checkboxes, std::map<std::string, std::vector<std::string>>& result);
	void recommendation(std::vector<std::string> searchstring, std::vector<std::string>& output);
	/*get data specific to the features*/
	std::vector<std::string> getFeatureNames(std::string searchString);
private:
	KeyWordSearch();
	~KeyWordSearch();
	/*this will act like a dictionary which will reduce the search time*/
	std::map<std::string, std::vector<std::string>> featuresMap;
	/*this will save the cleansed keywords string and it will be passed to the recommender system to get the associated restaurants*/
	std::vector<std::string> keyWords;

	const std::string fillFeatureMap(const std::string);
	/*fill up database*/
	void fillUpWithPreposition();
	std::vector<std::string>prepositionList;
	/*clean the filters*/
	std::vector<std::string> cleanTheFilter(std::string);
	/*remove all prepositions*/
	std::string removePreoposition(std::string featureName);
	/*binary search for quicker output*/
	bool binarySearch(std::string wordTocheck);
	/*percentage of match*/
	float percentageMatched(std::string keyword, std::string searchString) const;
	/**/
	void fetchData(std::vector<std::vector<std::string>> hits, std::vector<std::string>& result);
	//bool binarySearch(std::vector<std::string> arr,int low,int high,std::string val);

	
};

