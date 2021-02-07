#include "iostream"
#include "stdlib.h"
#include "string.h"
#include "Geotiff.cpp"
using namespace std; 
 
int main() { 
 
  // create object of Geotiff class
  Geotiff tiff((const char*)"/data/cpp_test/示例数据_out.tif");  
 
  // output a value from 2D array  
  float** rasterBandData = tiff.GetRasterBand(1) ; 
  cout << "value at row 1000, column 1000: " << rasterBandData[1000][1000] << endl; 
 
  // call other methods, like get the name of the Geotiff
  // passed-in, its length, and its projection string 
  cout << tiff.GetFileName() << endl ;
  cout << strlen( tiff.GetFileName() ) << endl ;
  cout << tiff.GetProjection() << endl;
   
  // dump out the Geotransform (6 element array of doubles) 
  double *gt = tiff.GetGeoTransform(); 
  cout << gt[0] << " " << gt[1] << " " << gt[2] << " " << gt[3] << " " << gt[4] << " " << gt[5] << endl; 
   
  // dump out Geotiff band NoData value (often it is -9999.0)
  cout << "No data value: " << tiff.GetNoDataValue() << endl;  
  
  // dump out array (band) dimensions of Geotiff data  
  int *dims = tiff.GetDimensions() ; 
  cout << dims[0] << " " << dims[1] << " " << dims[2] << endl;
 
  return 0;
}