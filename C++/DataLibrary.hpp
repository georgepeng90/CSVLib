#pragma once

#include "CSVReader.hpp"

#include <map>

#include "BasicData.h"
#include "StringModifier.h"

class DataLibrary
		: public CSVReader
{
 
public:

	DataLibrary()
	{

	}

	virtual ~DataLibrary()
	{
		clearLibrary();
	}

	virtual const BasicData& getDataByKey(int aId) const
	{
		std::map<int, BasicData*>::const_iterator itr = _library.find(aId);
		assert(itr != _library.end());
		return *(itr->second);
	}

	virtual const std::map<int, BasicData*>& getAllData() const
	{
		return _library;
	}

	virtual const BasicData* getDataPointerByKey(int aId) const
	{
		std::map<int, BasicData*>::const_iterator itr = _library.find(aId);
		assert(itr != _library.end());
		return itr->second;
	}

	int getDataRecordCount() const
	{
		return _library.size();
	}

	virtual bool loadDataFromResource(const std::string &aSource) override
	{
		if (_library.size() != 0)
		{
			clearLibrary();
		}

		return CSVReader::loadDataFromResource(aSource);
	}

protected:

	virtual void parseHead(const std::vector<std::string> &aData)
	{
		for (auto field : aData)
		{
			std::vector<std::string> split = StringModifier::split(
				field,
				"$");
			assert(split.size() > 1);
			_head.push_back(std::make_pair(split[0], split[1]));
		}
	}

	virtual void parseData(const std::vector<std::string> &aData)
	{
		assert(aData.size() == _head.size());

		BasicData *data = new BasicData();
		for (unsigned int i = 0; i < aData.size(); ++i)
		{
			data->parseData(
				_head[i].first,		// key
				_head[i].second,	// type
				aData[i]);			// value
		}

		_library[getDataKey(data)] = data;
	}

	virtual void parseLine(
		unsigned int aIndex,
		const std::vector<std::string> &aRow) override
	{
		if (aIndex == 0)
		{
			parseHead(aRow);
		}
		else
		{
			parseData(aRow);
		}
	}

	virtual int getDataKey(BasicData *aData) const
	{
		int key;
		(*aData)["id"] >> key;
		return key;
	}

	void clearLibrary()
	{
		for (auto dataInMap : _library)
		{
			if (dataInMap.second)
			{
				delete dataInMap.second;
			}
		}

		_library.clear();
		_head.clear();
	}

protected:

	std::vector<BasicData::DataHead> _head;
	std::map<int, BasicData*> _library;
};