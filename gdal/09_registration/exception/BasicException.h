/*
 *  BasicException.h
 *
 *   Common
 *
 *	A class providing the base BasicException for the 
 *	the  library
 *
 *  Created by Pete Bunting on 04/02/2008.
 *  Copyright 2008 Lib.
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

#ifndef BasicException_H
#define BasicException_H

#include <exception>
#include <iostream>
#include <string>

// #include "Commons.h"

// mark all exported classes/functions with DllExport to have
// them exported by Visual Studio
#undef DllExport
#ifdef _MSC_VER
    #ifdef rsgis_commons_EXPORTS
        #define DllExport   __declspec( dllexport )
    #else
        #define DllExport   __declspec( dllimport )
    #endif
#else
    #define DllExport
#endif

class DllExport BasicException : public std::exception
{
	public:
		BasicException();
		BasicException(const char *message);
		BasicException(std::string message);
		virtual ~BasicException();
		virtual const char* what() const noexcept;
	protected:
		std::string msgs;
};


#endif
