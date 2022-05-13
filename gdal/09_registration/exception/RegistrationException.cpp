/*
 *  RegistrationException.cpp
 *  _LIB
 *
 *  Created by Pete Bunting on 31/08/2010.
 *  Copyright 2010 Lib.
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

#include "RegistrationException.h"


RegistrationException::RegistrationException() : BasicException("A RegistrationException has been created..")
{
	
}


RegistrationException::RegistrationException(const char* message) : BasicException(message)
{
	
}

RegistrationException::RegistrationException(std::string message)  : BasicException(message)
{
	
}


