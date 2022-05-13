#include <iostream>
#include <cstring>
#include <string>
#include "gdal_priv.h"

using namespace std;

static void Usage( const char* pszErrorMsg = nullptr )
{
    printf("gray2rgb 0.1.0\n"
           "Convert gray image to rgb images.\n\n"
           "Usage: gray2rgb [--input </mnt/gray.tif> --output </mnt/rgb.tif> --rgb_value <255 255 255> --valid_value <1>]\n"
           "                [--help]\n"
           "\n"
           "OPTIONS:\n"
           "  --input </mnt/gray.tif>     Input image with only one band.\n"
           "  --output </mnt/rgb.tif>     Output image with three band in the RGB order.\n"
           "  --rgb_value <255 255 255>   The rgb value in the output image. [default: 255 255 255]\n"
           "  --valid_value <1>           The valid value in the input image. [default: 1]\n");

    if( pszErrorMsg != nullptr )
        fprintf(stderr, "\nFAILURE: %s\n", pszErrorMsg);

    exit(1);
}

int main(int argc, char *argv[])
{
    for(int iArg = 0; iArg < argc; iArg++){
        string s(argv[iArg]);
		if(s == "--help")
        {
            Usage();
        }
        else if(s.substr(0,7) == "--input")
        {
            
            cout << s << "end" << endl;
            // printf("--input\n");
        }
	}
	return 0;

}