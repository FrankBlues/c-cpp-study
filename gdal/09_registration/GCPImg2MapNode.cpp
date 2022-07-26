/*
 *  GCPImg2MapNode.cpp
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

#include "GCPImg2MapNode.h"


GCPImg2MapNode::GCPImg2MapNode(double eastings, double northings, float imgXIn, float imgYIn): eastings_(0), northings_(0), imgX_(0), imgY_(0)
{
	this->eastings_ = eastings;
	this->northings_ = northings;
	this->imgX_ = imgXIn;
	this->imgY_ = imgYIn;
}

double GCPImg2MapNode::eastings() const
{
	return eastings_;
}

double GCPImg2MapNode::northings() const
{
	return northings_;
}


float GCPImg2MapNode::imgX() const
{
	return imgX_;
}

float GCPImg2MapNode::imgY() const
{
	return imgY_;
}

double GCPImg2MapNode::distanceGeo(GCPImg2MapNode *pt)
{
	double sqSum = ((this->eastings_ - pt->eastings_)*(this->eastings_ - pt->eastings_)) + ((this->northings_ - pt->northings_)*(this->northings_ - pt->northings_));
	
	return sqrt(sqSum/2);
}

GCPImg2MapNode::~GCPImg2MapNode()
{
	
}
	


