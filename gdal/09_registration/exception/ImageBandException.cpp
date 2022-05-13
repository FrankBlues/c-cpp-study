/*
 *  ImageBandException.cpp
 *  
 *   IMG
 *
 *	A class providing the Exception for errors associated
 *	with image bands the  library
 *
 *  Created by Pete Bunting on 10/04/2008.
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

#include "ImageBandException.h"



ImageBandException::ImageBandException() : ImageException("A ImageBandException has been created..")
{
	
}

ImageBandException::ImageBandException(const char* message) : ImageException(message)
{

}

ImageBandException::ImageBandException(std::string message) : ImageException(message)
{
	
}
	
