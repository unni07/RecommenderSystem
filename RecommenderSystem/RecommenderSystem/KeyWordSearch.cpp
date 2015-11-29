#include "precompiled.h"
#include "KeyWordSearch.h"
#include "Features.h"


KeyWordSearch& KeyWordSearch::getInstance()
{
	static KeyWordSearch ks;
	return ks;
}

void KeyWordSearch::initialize()
{

	fillUpWithPreposition();
	cleanTheFilter("something");
	
	auto listOfFeatures =  FeatureDatabase::GetFeatureNameList();
	auto itr = listOfFeatures.begin();
	auto itrEnd = listOfFeatures.end();
	while (itr != itrEnd)
	{
		std::vector<std::string> cleansedFilter = cleanTheFilter(*itr);
		auto itrV = cleansedFilter.begin();
		auto endItr = cleansedFilter.end();
		while(itrV !=endItr)
		{
			//std::sort(itrV->begin(), itrV->end());
			featuresMap[*itrV].push_back(*itr);
			++itrV;
		}
		/*char  firstchar = (*itr).at(0);
		auto findinMap = featuresMap.find(firstchar);
		featuresMap[firstchar].push_back(*itr);*/

		++itr;
	}
	search("I feel like Eating in historic place");
}

void KeyWordSearch::search(std:: string name)
{
	if (name.size() == 0)
		return;
	
	/*
	search string "SOmething historical"
	feature name:: history
	*/

	std::transform(name.begin(), name.end(), name.begin(), tolower);
	std::vector<std::string> cleansedSearchString = cleanTheFilter(name);
	
	std::vector<std::string> hits;
	auto itrVector = cleansedSearchString.begin();
	auto itrVectorEnd = cleansedSearchString.end();
	while (itrVector != itrVectorEnd)
	{
		auto itr = featuresMap.begin();
		auto itrEnd = featuresMap.end();
		while (itr != itrEnd)
		{
			if(itr->first == "historic")
			{
				int a = 10;
			}
			auto percentage = percentageMatched(itr->first, *itrVector);
			
			if (percentage >= 70.0f)
			{
				hits.push_back(itr->first);
			}
			++itr;
		}
		++itrVector;
	}
	
	
}

KeyWordSearch::KeyWordSearch()
{
	prepositionList.reserve(1000);
}


KeyWordSearch::~KeyWordSearch()
{
}

const std::string KeyWordSearch::fillFeatureMap(const std::string)
{
	std::string name(" ");
	return name;
}

void KeyWordSearch::fillUpWithPreposition()
{
	std::ifstream file;
	file.open("prepositionList.txt");
	std::string line;
	while (std::getline(file, line))
	{
		prepositionList.push_back(line);
	}
	file.close();
	std::sort(prepositionList.begin(), prepositionList.end());
}

std::vector<std::string> KeyWordSearch::cleanTheFilter(std::string keystring)
{
	std::vector<std::string> listKeyWords;

	std::string cleansedFilter = removePreoposition(keystring);

	std::istringstream iss(cleansedFilter);
	std::string word;
	while(iss>>word)
	{
		listKeyWords.push_back(word);
	}
	return listKeyWords;
}

std::string KeyWordSearch::removePreoposition(std::string featureName)
{
	std::istringstream iss(featureName);
	std::string word;
	std::string output;
	while(iss>>word)
	{
		if(!binarySearch(word))
		{
			output = output + word;
			output = output + " ";
		}
	}

	return output;
}

bool KeyWordSearch::binarySearch(std::string wordTocheck)
{
	unsigned int low = 0;
	size_t high = prepositionList.size() - 1;
	unsigned int middle;

	while((high - low) > 1)
	{
		middle = (high + low) / 2;
		if(prepositionList[middle].compare(wordTocheck) == 0)
		{
			return true;
		}
		if(prepositionList[middle]<wordTocheck)
		{
			low = middle;
		}
		else
		{
			high = middle;
		}
	}
	return false;
}

float KeyWordSearch::percentageMatched(std::string keyword, std::string searchString) const
{
	
	size_t sizeKeyWord = keyword.size();
	size_t sizesearchString = searchString.size();

	if (sizeKeyWord <= 1 || sizesearchString <= 1)
		return 0.0f;
	//std::sort(keyword.begin(), keyword.end());
	//std::sort(searchString.begin(), searchString.end());
	size_t minSize = std::min(sizeKeyWord, sizesearchString);


	if(strstr(keyword.c_str(),searchString.c_str()) || strstr(searchString.c_str(), keyword.c_str()))
	{
		return 100.0f;
	}
	int percentage =static_cast<int>( minSize * 0.7f);
	std::string str1 = keyword.substr(0, percentage);
	std::string str2 = searchString.substr(0, percentage);
	if (strstr(str2.c_str(), str1.c_str()) || strstr(str1.c_str(), str2.c_str()))
	{
		return 70.0f;
	}
	
	return 0.0f;
	/*
	historical
	history
	*/

}
