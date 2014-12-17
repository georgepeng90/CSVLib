#pragma once

#include "../csv_parser/csv_parser.hpp"

class CSVReader
{
public:

	virtual bool loadDataFromResource(const std::string &aSource)
	{
		const char fieldTerminator = ',';
		const char lineTerminator  = '\n';
		const char enclosureChar   = '\"';

		csv_parser fileParser;

		/* Define how many records we're gonna skip. This could be used to skip the column definitions. */
		fileParser.set_skip_lines(0);
		/* Specify the file to parse */
		if (!fileParser.init(aSource.c_str()))
		{
			return false;
		}
		/* Here we tell the parser how to parse the file */
		fileParser.set_enclosed_char(enclosureChar, ENCLOSURE_OPTIONAL);
		fileParser.set_field_term_char(fieldTerminator);
		fileParser.set_line_term_char(lineTerminator);

		/* Check to see if there are more records, then grab each row one at a time */
		unsigned int lineIndex = 0;
		while(fileParser.has_more_rows())
		{
			/* Get the record */
			std::vector<std::string> row = fileParser.get_row();
			this->parseLine(lineIndex, row);
			++lineIndex;
		}

		return true;
	}

protected:

	virtual void parseLine(
		unsigned int aIndex, 
		const std::vector<std::string> &aRow) = 0;
};