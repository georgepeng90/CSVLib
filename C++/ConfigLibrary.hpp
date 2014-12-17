#pragma once

#include "CSVReader.hpp"

#include "BasicData.h"
#include "StringModifier.h"

class ConfigLibrary
	: public CSVReader
{
public:

	ConfigLibrary()
	{

	}
	virtual ~ConfigLibrary()
	{

	}

	const DataUnit& operator [] (const std::string& aKey) const
	{
		return _data[aKey];
	}
	const DataUnit& getConfig(const std::string aKey) const
	{
		return _data[aKey];
	}

protected:

	virtual void parseLine(
		unsigned int aIndex, 
		const std::vector<std::string> &aRow) override
	{
		assert(aRow.size() == 2);
		std::string head = aRow[0];
		std::vector<std::string> splitedHead = StringModifier::split(
			head,
			"$");
		assert(splitedHead.size() == 2);
		std::string key = splitedHead[0];
		std::string type = splitedHead[1];

		std::string value = aRow[1];

		_data.parseData(
			key,
			type,
			value);
	}

	BasicData _data;
};
