/*
 *  AddGCPsGDAL.h
 *  _LIB
 *
 *  Created by Daniel Clewley on 06/06/2013.
 *  Copyright 2013 Lib. All rights reserved.
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

#ifndef AddGCPsGDAL_H
#define AddGCPsGDAL_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <list>

#include "gdal_priv.h"
#include "ogrsf_frmts.h"

#include "utils/TextUtils.h"
#include "exception/ImageException.h"
#include "math/MathsUtils.h"

#include "img/ImageUtils.h"
#include "common/rsgis-tqdm.h"

#include "GCPImg2MapNode.h"

// mark all exported classes/functions with DllExport to have
// them exported by Visual Studio
#undef DllExport
#ifdef _MSC_VER
    #ifdef rsgis_registration_EXPORTS
        #define DllExport   __declspec( dllexport )
    #else
        #define DllExport   __declspec( dllimport )
    #endif
#else
    #define DllExport
#endif
    
class DllExport AddGCPsGDAL
{
public:
    AddGCPsGDAL(std::string inFileName, std::string gcpFilePath, std::string outFileName = "",  std::string gdalFormat = "KEA", GDALDataType gdalDataType = GDT_Float32);
    void readGCPFile(std::string gcpFilePath, std::vector<GCPImg2MapNode*> *gcps);
    void convert2GDALGCP(std::vector<GCPImg2MapNode*> *gcps, GDAL_GCP *gdalGCPList);
    void copyImageWithoutSpatialRef(std::string inFileName, std::string outFileName, std::string gdalFormat, GDALDataType gdalDataType);
    ~AddGCPsGDAL(){};
};

#endif





