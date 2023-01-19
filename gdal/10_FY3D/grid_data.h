#ifndef GRIDA_DATA
#define GRIDA_DATA
#include <vector>
#include <algorithm>
#include "gdal_priv.h"
#include "gdalgrid.h"
#include "utils.h"

void grid_data_to_raster(const std::vector<double> &x, const std::vector<double> &y,
                      const std::vector<double> &z, const char* pszDest,
                      const double res, GDALDataType eType, const char* pszAlgorithm);


#endif