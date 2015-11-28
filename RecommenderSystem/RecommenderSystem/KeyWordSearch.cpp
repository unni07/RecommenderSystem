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
		char  firstchar = (*itr).at(0);
		auto findinMap = featuresMap.find(firstchar);
		featuresMap[firstchar].push_back(*itr);

		++itr;
	}

}

void KeyWordSearch::search(std:: string name)
{
	if (name.size() == 0)
		return;

	/*
	search string "SOmething historical"
	feature name:: history


	*/
	
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

	removePreoposition("Hello is there entree");

	return {};
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
	unsigned int high = prepositionList.size() - 1;
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
