/*
 *  GCPImg2MapNode.h
 *  _LIB
 *
 *  Created by Pete Bunting on 06/09/2010.
 *  Copyright 2010 Lib. All rights reserved.
 *
 * This file is part of Lib.
 * 
 * Lib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lib.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef GCPImg2MapNode_H
#define GCPImg2MapNode_H

#include <cmath>

// #include "common/Commons.h"

// mark all exported classes/functions with DllExport to have
// them exported by Visual Studio
#undef DllExport
#ifdef _MSC_VER
    #ifdef _registration_EXPORTS
        #define DllExport   __declspec( dllexport )
    #else
        #define DllExport   __declspec( dllimport )
    #endif
#else
    #define DllExport
#endif

	
class DllExport GCPImg2MapNode
{
public:
	GCPImg2MapNode(double eastings, double northings, float imgXIn, float imgYIn);
	double eastings() const;
	double northings() const;
	float imgX() const;
	float imgY() const;
	double distanceGeo(GCPImg2MapNode *pt);
	~GCPImg2MapNode();
protected:
	double eastings_;
	double northings_;
	float imgX_;
	float imgY_;
};

#endif




