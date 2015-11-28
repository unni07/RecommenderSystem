#pragma once
class KeyWordSearch
{
public:
	static KeyWordSearch& getInstance();
	void initialize();
	void search(std::string name);
private:
	KeyWordSearch();
	~KeyWordSearch();
	/*this will act like a dictionary which will reduce the search time*/
	std::map<char, std::vector<std::string>> featuresMap;
	/*this will save the cleansed keywors string and it will be passed to the recommender system to get the associated resturants*/
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
};

