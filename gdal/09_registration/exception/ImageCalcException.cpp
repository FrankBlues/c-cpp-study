/*
 *  ImageCalcException.cpp
 *  _LIB
 *
 *  Created by Pete Bunting on 23/04/2008.
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

#include "ImageCalcException.h"

	
ImageCalcException::ImageCalcException() : ImageException("A ImageBandException has been created..")
{

}

ImageCalcException::ImageCalcException(const char* message) : ImageException(message)
{

}

ImageCalcException::ImageCalcException(std::string message) : ImageException(message)
{
	
}
	

