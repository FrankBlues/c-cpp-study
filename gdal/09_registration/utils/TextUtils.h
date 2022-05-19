/*
 *  TextUtils.h
 *  _LIB
 *
 *  Created by Pete Bunting on 26/05/2008.
 *  Copyright 2008 Lib. All rights reserved.
 *  This file is part of Lib.
 * 
 *  Lib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Lib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Lib.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TextUtils_H
#define TextUtils_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "exception/TextException.h"

#include <boost/numeric/conversion/cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/cstdint.hpp>
#include <boost/algorithm/string/trim.hpp>

// mark all exported classes/functions with DllExport to have
// them exported by Visual Studio
#undef DllExport
#ifdef _MSC_VER
    #ifdef rsgis_utils_EXPORTS
        #define DllExport   __declspec( dllexport )
    #else
        #define DllExport   __declspec( dllimport )
    #endif
#else
    #define DllExport
#endif


inline bool compareStringNoCase(std::string first, std::string second)
{
	unsigned int i=0;
	while( (i < first.length()) && (i < second.length()))
	{
		if (tolower(first[i])<tolower(second[i]))
		{
			return true;
		}
		else if (tolower(first[i])>tolower(second[i]))
		{
			return false;
		}
		++i;
	}
	if(first.length() < second.length())
	{
		return true;
	}
	else
	{
		return false;
	}
};

class DllExport TextUtils
	{
	public:
		TextUtils();
		size_t countLines(std::string input);
		void transpose(std::string input, std::string output, std::string delimiter);
		bool lineStart(std::string line, char token);
		bool blankline(std::string line);
		void tokenizeString(std::string line, char token, std::vector<std::string> *tokens, bool ignoreDuplicateTokens=true, bool trimWhitespace=false);
		std::string removeNewLine(std::string line);
		
		std::string readFileToString(std::string input);
		std::vector<std::string> readFileToStringVector(std::string input);
		void writeStringToFile(std::string file, std::string output);
		
		double strtodouble(std::string inValue);
		float strtofloat(std::string inValue);
		
		int strtoInt(std::string inValue);
		unsigned int strtoUInt(std::string inValue);
		
		long strtoLong(std::string inValue);
		unsigned long strtoULong(std::string inValue);
		
		uint_fast8_t strto8bitUInt(std::string inValue);
		uint_fast16_t strto16bitUInt(std::string inValue);
		uint_fast32_t strto32bitUInt(std::string inValue);
		uint_fast64_t strto64bitUInt(std::string inValue);
		
		int_fast8_t strto8bitInt(std::string inValue);
		int_fast16_t strto16bitInt(std::string inValue);
		int_fast32_t strto32bitInt(std::string inValue);
		int_fast64_t strto64bitInt(std::string inValue);
		size_t strtosizet(std::string inValue);
		
		std::string doubletostring(double number);
		std::string floattostring(float number);
		
		std::string uInt8bittostring(uint_fast8_t number);
		std::string uInt16bittostring(uint_fast16_t number);
		std::string uInt32bittostring(uint_fast32_t number);
		std::string uInt64bittostring(uint_fast64_t number);
		
		std::string int8bittostring(int_fast8_t number);
		std::string int16bittostring(int_fast16_t number);
		std::string int32bittostring(int_fast32_t number);
		std::string int64bittostring(int_fast64_t number);
		std::string sizettostring(size_t number);
		
		std::string inttostring(int number);
		std::string uInttostring(unsigned int number);
		std::string longtostring(long number);
		std::string uLongtostring(unsigned long number);
		
		~TextUtils();
	};

class DllExport TextFileLineReader
{
public:
	TextFileLineReader();
	void openFile(std::string filepath);
	bool endOfFile();
	std::string readLine();
	void closeFile();
	~TextFileLineReader();	
private:
	std::ifstream inputFileStream;
	bool fileOpened;
};


#endif
