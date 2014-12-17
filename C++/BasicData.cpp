#include "BasicData.h"

#include <vector>
#include <map>
#include <stdlib.h>

#include "StringModifier.h"

BasicData::BasicData()
{

}

BasicData::~BasicData()
{

}

const DataUnit& BasicData::operator[](const std::string& aKey) const
{
	std::string lowerKey = StringModifier::toLowerCase(aKey);
	std::map<std::string, DataUnit>::const_iterator itr = _data.find(lowerKey);
	assert(itr != _data.end());
	return itr->second;
}

const DataUnit* BasicData::getField(const std::string& aKey) const
{
	std::string lowerKey = StringModifier::toLowerCase(aKey);
	std::map<std::string, DataUnit>::const_iterator itr = _data.find(lowerKey);
	assert(itr != _data.end());
	return &(itr->second);
}

void BasicData::parseData(
	const std::string &aKey,
	const std::string &aType, 
	const std::string &aValue)
{
	std::string key = StringModifier::toLowerCase(aKey);

	if (aType == "string")
	{
		_data[key] << aValue.c_str();
	}
	else if (aType == "int")
	{
		_data[key] << atoi(aValue.c_str());
	}
	else if (aType == "float")
	{
		_data[key] << (float)atof(aValue.c_str());
	}
}
