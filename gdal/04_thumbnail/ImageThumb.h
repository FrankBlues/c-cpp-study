#ifndef IMAGETHUMB_H
#define IMAGETHUMB_H
#pragma once

#include <gdal_priv.h>

// 生成单波段灰度缩略图
bool CreateThumbnail(const char* input, const char* output, int bandID,
                     float scale);

// 生成RGB彩色缩略图
bool CreateThumbnail(const char* input, const char* output, int redBand,
                     int greenBand, int blueBand, float scale);

#endif