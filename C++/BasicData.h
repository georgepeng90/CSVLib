#pragma once

#include <string>
#include <map>
#include <vector>
#include <assert.h>

class DataUnit
{
public:

	typedef enum
	{
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_STRING
	} DataType;

	DataUnit()
		: _data(NULL)
	{

	}

	DataUnit(const DataUnit &aRight)
	{
		switch (aRight._type)
		{
		case TYPE_FLOAT:
			(*this) << *((float*)aRight._data);
			break;
		case TYPE_INT:
			(*this) << *((int*)aRight._data);
			break;
		case TYPE_STRING:
			(*this) << (char*)aRight._data;
			break;
		}
	}

	~DataUnit()
	{
		releaseContent();
	}

	template <typename T>
	DataUnit& operator << (T aValue)
	{
		// type not available
		assert(NULL);

		return *this;
	}

	DataUnit& operator << (float aValue)
	{
		releaseContent();
		_data = new float;
		_type = TYPE_FLOAT;
		memcpy(_data, &aValue, sizeof(float));

		return *this;
	}

	DataUnit& operator << (int aValue)
	{
		releaseContent();
		_data = new int;
		_type = TYPE_INT;
		memcpy(_data, &aValue, sizeof(int));

		return *this;
	}

	DataUnit& operator << (const char *aValue)
	{
		releaseContent();
		int len = strlen(aValue);
		_data = new char[len + 1];
		_type = TYPE_STRING;
		memset(_data, 0, (len + 1) * sizeof(char));
		strcpy((char*)_data, aValue);

		return *this;
	}

	template <typename T>
	const DataUnit& operator >> (T& aValue) const
	{
		// type not available
		assert(NULL);

		return *this;
	}

	const DataUnit& operator >> (float& aValue) const
	{
		aValue = toFloat();

		return *this;
	}

	const DataUnit& operator >> (int& aValue) const
	{
		aValue = toInt();

		return *this;
	}

	const DataUnit& operator >> (std::string& aValue) const
	{
		aValue = toString();

		return *this;
	}

	std::string toString() const
	{
		assert(_type == TYPE_STRING);
		return std::string((char*)_data);
	}

	int toInt() const
	{
		assert(_type == TYPE_INT);
		return *(int*)_data;
	}

	float toFloat() const
	{
		assert(_type == TYPE_FLOAT);
		return *(float*)_data;
	}

protected:

	void releaseContent()
	{
		if (_data)
		{
			switch (_type)
			{
			case TYPE_INT:
				delete (int*)_data;
				break;
			case TYPE_FLOAT:
				delete (float*)_data;
				break;
			case TYPE_STRING:
				delete[](char*)_data;
				break;
			default:
				// should not arrive here
				assert(NULL);
				break;
			}

			_data = NULL;
		}
	}

	int _type;
	void *_data;
};

class BasicData
{
public:

	BasicData();
	virtual ~BasicData();

	typedef std::pair<std::string, std::string> DataHead; // key , type

	const DataUnit& operator [] (const std::string& aKey) const;
	const DataUnit* getField(const std::string& aKey) const;

	void parseData(
		const std::string &aKey,
		const std::string &aType,
		const std::string &aValue);

protected:

	std::map<std::string, DataUnit> _data;
};
