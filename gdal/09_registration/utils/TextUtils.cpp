/*
 *  TextUtils.cpp
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

#include "TextUtils.h"

	
TextUtils::TextUtils()
{
	
}

size_t TextUtils::countLines(std::string input)
{
	size_t count = 0;
	std::ifstream inputFile;
	inputFile.open(input.c_str());
	if(inputFile.is_open())
	{
		std::string strLine;		
		while(!inputFile.eof())
		{
			getline(inputFile, strLine, '\n');
			if(strLine.size() > 0)
			{
				count++;
			}
		}
	}
	else
	{
		std::string message = std::string("Text file ") + input + std::string(" could not be openned.");
		throw TextException(message.c_str());
	}
	
	return count;
}

void TextUtils::transpose(std::string input, std::string output, std::string delimiter)
{
	
}

bool TextUtils::lineStart(std::string line, char token)
{
	int lineLength = line.length();
	for(int i = 0; i < lineLength; i++)
	{
		if(line.at(i) == ' ' | line.at(i) == '\t' | line.at(i) == '\n')
		{
			// spaces and tabs at the beginning of a line can be ignored.
		}
		else if(line.at(i) == token)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool TextUtils::blankline(std::string line)
{
	int lineLength = line.length();
	if(lineLength == 1)
	{
		return true;
	}
	else
	{
		for(int i = 0; i < lineLength; i++)
		{
			if(line.at(i) == ' ' | line.at(i) == '\t' | line.at(i) == '\n')
			{
				// spaces and tabs at the beginning of a line can be ignored.
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

void TextUtils::tokenizeString(std::string line, char token, std::vector<std::string> *tokens, bool ignoreDuplicateTokens, bool trimWhitespace)
{
	std::string word;
	int start = 0;
	int lineLength = line.length();
	for(int i = 0; i < lineLength; i++)
	{
		if(line.at(i) == token)
		{
			word = boost::algorithm::trim_copy(line.substr(start, i-start));								
			if(ignoreDuplicateTokens)
			{
				if(word.length() > 0)
				{
					if(trimWhitespace)
					{
						boost::trim(word);
					}
					tokens->push_back(word);
				}
			}
			else 
			{
				if(trimWhitespace)
				{
					boost::trim(word);
				}
				tokens->push_back(word);
			}
			
			start = start + i-start+1;
		}
	}
	word = line.substr(start);
	if(trimWhitespace)
	{
		boost::trim(word);
	}
	tokens->push_back(word);
}

std::string TextUtils::removeNewLine(std::string line)
{
	int lineLength = line.length();
	std::string output = line.substr(0, lineLength-1);
	return output;
}

std::string TextUtils::readFileToString(std::string input)
{
	std::string wholeFile = "";
	std::ifstream inputFileStream;
	inputFileStream.open(input.c_str(), std::ios_base::in);
	if(!inputFileStream.is_open())
	{
		throw TextException("File could not be opened.");
	}
	
	std::string strLine = "";
	bool lineEnding = false;
	char ch, lastch;
	inputFileStream.get(ch);
	while (!inputFileStream.eof()) 
	{					
		if ((ch == 0x0a) && (lastch == 0x0d))
		{
			lineEnding = true; // Windows Line Ending
		}
		else if ((lastch == 0x0d) && (ch != 0x0a)) 
		{
			lineEnding = true; // Mac Line Ending
		} 
		else if (ch == 0x0a) 
		{
			lineEnding = true; // UNIX Line Ending
		}
		
		if(lineEnding)
		{
			boost::algorithm::trim(strLine);
			wholeFile += strLine;
			strLine = "";
			lineEnding = false;
		}
		else 
		{
			strLine += ch;
		}
		
		lastch = ch;
		inputFileStream.get(ch);
	}
	boost::algorithm::trim(strLine);
	wholeFile += strLine;
	inputFileStream.close();
	
	return wholeFile;
}

std::vector<std::string> TextUtils::readFileToStringVector(std::string input)
{
	std::vector<std::string> wholeFile;
	std::ifstream inputFileStream;
	inputFileStream.open(input.c_str(), std::ios_base::in);
	if(!inputFileStream.is_open())
	{
		throw TextException("File could not be opened.");
	}
	
	std::string strLine = "";
	bool lineEnding = false;
	char ch, lastch;
	inputFileStream.get(ch);
	while (!inputFileStream.eof())
	{
		if ((ch == 0x0a) && (lastch == 0x0d))
		{
			lineEnding = true; // Windows Line Ending
		}
		else if ((lastch == 0x0d) && (ch != 0x0a))
		{
			lineEnding = true; // Mac Line Ending
		}
		else if (ch == 0x0a)
		{
			lineEnding = true; // UNIX Line Ending
		}
		
		if(lineEnding)
		{
			boost::algorithm::trim(strLine);
			wholeFile.push_back(strLine);
			strLine = "";
			lineEnding = false;
		}
		else
		{
			strLine += ch;
		}
		
		lastch = ch;
		inputFileStream.get(ch);
	}
	boost::algorithm::trim(strLine);
	wholeFile.push_back(strLine);
	inputFileStream.close();
	
	return wholeFile;
}

void TextUtils::writeStringToFile(std::string file, std::string output)
{
	try 
	{
		std::ofstream outFile;
		outFile.open(file.c_str());
		if(outFile.is_open())
		{
			outFile << output << std::endl;
			outFile.flush();
			outFile.close();
		}
		else 
		{
			std::string message = std::string("File \'") + file + std::string("\' could not be created.");
			throw TextException(message);
		}
		
	}
	catch (TextException &e)
	{
		throw e;
	}
}

double TextUtils::strtodouble(std::string inValue)
{
	double outValue = 0;
	try
	{
		outValue = boost::lexical_cast<double>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

float TextUtils::strtofloat(std::string inValue)
{
	float outValue = 0;
	try
	{
		outValue = boost::lexical_cast<float>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}


int TextUtils::strtoInt(std::string inValue)
{
	int outValue = 0;
	try
	{
		outValue = boost::lexical_cast<int>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

unsigned int TextUtils::strtoUInt(std::string inValue)
{
	unsigned int outValue = 0;
	try
	{
		outValue = boost::lexical_cast<unsigned int>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

long TextUtils::strtoLong(std::string inValue)
{
	long outValue = 0;
	try
	{
		outValue = boost::lexical_cast<long>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

unsigned long TextUtils::strtoULong(std::string inValue)
{
	unsigned long outValue = 0;
	try
	{
		outValue = boost::lexical_cast<unsigned long>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

uint_fast8_t TextUtils::strto8bitUInt(std::string inValue)
{
	uint_fast8_t outValue = 0;
	try
	{
		outValue = boost::lexical_cast<uint_fast8_t>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

uint_fast16_t TextUtils::strto16bitUInt(std::string inValue)
{
	uint_fast16_t outValue = 0;
	try
	{
		outValue = boost::lexical_cast<uint_fast16_t>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

uint_fast32_t TextUtils::strto32bitUInt(std::string inValue)
{
	uint_fast32_t outValue = 0;
	try
	{
		outValue = boost::lexical_cast<uint_fast32_t>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

uint_fast64_t TextUtils::strto64bitUInt(std::string inValue)
{
	uint_fast64_t outValue = 0;
	try
	{
		outValue = boost::lexical_cast<uint_fast64_t>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

int_fast8_t TextUtils::strto8bitInt(std::string inValue)
{
	int_fast8_t outValue = 0;
	try
	{
		outValue = boost::lexical_cast<int_fast8_t>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

int_fast16_t TextUtils::strto16bitInt(std::string inValue)
{
	int_fast16_t outValue = 0;
	try
	{
		outValue = boost::lexical_cast<int_fast16_t>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

int_fast32_t TextUtils::strto32bitInt(std::string inValue)
{
	int_fast32_t outValue = 0;
	try
	{
		outValue = boost::lexical_cast<int_fast32_t>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

int_fast64_t TextUtils::strto64bitInt(std::string inValue)
{
	int_fast64_t outValue = 0;
	try
	{
		outValue = boost::lexical_cast<int_fast64_t>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

size_t TextUtils::strtosizet(std::string inValue)
{
	size_t outValue = 0;
	try
	{
		outValue = boost::lexical_cast<size_t>(inValue);
	}
	catch(boost::bad_lexical_cast &e)
	{
		std::string message = std::string("Trying to convert \"") + inValue + std::string("\" - ") + std::string(e.what());
		throw TextException(message);
	}
	return outValue;
}

std::string TextUtils::doubletostring(double number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::floattostring(float number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::uInt8bittostring(uint_fast8_t number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::uInt16bittostring(uint_fast16_t number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::uInt32bittostring(uint_fast32_t number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::uInt64bittostring(uint_fast64_t number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::int8bittostring(int_fast8_t number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::int16bittostring(int_fast16_t number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::int32bittostring(int_fast32_t number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::int64bittostring(int_fast64_t number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::sizettostring(size_t number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}


std::string TextUtils::inttostring(int number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::uInttostring(unsigned int number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::longtostring(long number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}

std::string TextUtils::uLongtostring(unsigned long number)
{
	std::string outValue = "";
	try
	{
		outValue = boost::lexical_cast<std::string>(number);
	}
	catch(boost::bad_lexical_cast &e)
	{
		throw TextException(e.what());
	}
	return outValue;
}
	
TextUtils::~TextUtils()
{
	
}





TextFileLineReader::TextFileLineReader(): inputFileStream(), fileOpened(false)
{
	
}

void TextFileLineReader::openFile(std::string filepath)
{
	inputFileStream.open(filepath.c_str(), std::ios_base::in);
	if(!inputFileStream.is_open())
	{
		throw TextException("File could not be opened.");
	}
	fileOpened = true;
}

bool TextFileLineReader::endOfFile()
{
	if(fileOpened)
	{
		return inputFileStream.eof();
	}
	return true;
}

std::string TextFileLineReader::readLine()
{
	std::string strLine = "";
	bool lineEnding = false;
	char ch, lastch;
	inputFileStream.get(ch);
	while (!inputFileStream.eof()) 
	{					
		if ((ch == 0x0a) && (lastch == 0x0d))
		{
			lineEnding = true; // Windows Line Ending
			inputFileStream.unget();
		}
		else if ((lastch == 0x0d) && (ch != 0x0a)) 
		{
			lineEnding = true; // Mac Line Ending
			inputFileStream.unget();
		} 
		else if (ch == 0x0a) 
		{
			lineEnding = true; // UNIX Line Ending
		}
		
		if(lineEnding)
		{
			break;
		}
		else 
		{
			strLine += ch;
		}
		
		lastch = ch;
		inputFileStream.get(ch);      
	}
	
	boost::algorithm::trim(strLine);
	
	return strLine;
}

void TextFileLineReader::closeFile()
{
	inputFileStream.close();
	fileOpened = false;
}

TextFileLineReader::~TextFileLineReader()
{
	
}


