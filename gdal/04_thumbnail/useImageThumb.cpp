#include <iostream>
#include "ImageThumb.h"

int main(int argc, char const *argv[])
{
    const char* imageFileName = "/data/cpp_test/S2B.tif";
    CreateThumbnail( imageFileName , "/data/cpp_test/S2B.jpg" , 1 , 0.2f );
    return 0;
}
