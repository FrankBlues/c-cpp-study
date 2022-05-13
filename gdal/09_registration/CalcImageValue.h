/*
 *  CalcImageValue.h
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

#ifndef CalcImageValue_H
#define CalcImageValue_H

#include <iostream>
#include <string>
#include "exception/ImageCalcException.h"

#include "gdal_priv.h"

// mark all exported classes/functions with DllExport to have
// them exported by Visual Studio
#undef DllExport
#ifdef _MSC_VER
    #ifdef rsgis_img_EXPORTS
        #define DllExport   __declspec( dllexport )
    #else
        #define DllExport   __declspec( dllimport )
    #endif
#else
    #define DllExport
#endif


class DllExport CalcImageValue
{
    public:
        CalcImageValue(int numberOutBands);
        virtual void calcImageValue(float *bandValues, int numBands, double *output) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(float *bandValues, int numBands, double *output, double *outRefVal, unsigned int nOutRefVals) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(float *bandValues, int numBands) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(long *intBandValues, unsigned int numIntVals, float *floatBandValues, unsigned int numfloatVals) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(long *intBandValues, unsigned int numIntVals, float *floatBandValues, unsigned int numfloatVals, double *output) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(long *intBandValues, unsigned int numIntVals, float *floatBandValues, unsigned int numfloatVals, double *output, double *outRefVal, unsigned int nOutRefVals) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(long *intBandValues, unsigned int numIntVals, float *floatBandValues, unsigned int numfloatVals, OGREnvelope extent) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(float *bandValues, int numBands, OGREnvelope extent) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(float *bandValues, int numBands, double *output, OGREnvelope extent) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(float ***dataBlock, int numBands, int winSize, double *output) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual void calcImageValue(float ***dataBlock, int numBands, int winSize, double *output, double *outRefVal, unsigned int nOutRefVals) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        /**
         * Extent only refers to the central window.
         */
        virtual void calcImageValue(float ***dataBlock, int numBands, int winSize, double *output, OGREnvelope extent) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual bool calcImageValueCondition(float ***dataBlock, int numBands, int winSize, double *output) {throw ImageCalcException("Not Implemented - CalcImageValue Base Class");};
        virtual int getNumOutBands();
        virtual void setNumOutBands(int bands);
        virtual ~CalcImageValue(){};
    protected:
        int numOutBands;
};



class DllExport CalcValuesFromMultiResInputs
{
public:
    CalcValuesFromMultiResInputs(int numberOutBands);
    virtual void calcImageValue(float *bandValues, int numInVals, bool useNoData, float noDataVal, double *output)  = 0;
    virtual int getNumOutBands();
    virtual void setNumOutBands(int bands);
    virtual ~CalcValuesFromMultiResInputs();
protected:
    int numOutBands;
};
    

#endif


