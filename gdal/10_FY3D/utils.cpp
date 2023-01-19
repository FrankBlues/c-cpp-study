#include <iostream>
#include "utils.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

bool endswithStr(const string &s, const string &end)
{
    return s.rfind(end) == (s.size() - end.size());
}

void splitStr(const string &str, const char &c, vector<string> &res)
{
	res.clear();
	string::size_type pos1, pos2;
	pos2 = str.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		res.push_back(str.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
		pos2 = str.find(c, pos1);
	}
	res.push_back(str.substr(pos1));
}

const char *getDriverName(const char *fileName)
{
    string s(fileName);
    const vector<const char*> tifV{"tif", "tiff", "TIF", "TIFF"};
    const vector<const char*> imgV{"img", "IMG"};
    for (auto &e: tifV)
    {
        if (endswithStr(s, e))
            return "GTiff";
    }
    for (auto &e: imgV)
    {
        if (endswithStr(s, e))
            return "HFA";
    }
    return nullptr;
}

// int main(int argc, char const *argv[])
// {
//     const string s("/mnt/asdgre.tif");
//     const char* algo = "invdistnn:radius=0.04:nodata=0:max_points=4:min_points=1";
//     // cout << getDriverName("/mnt/asdgre.img") << endl;
//     const string a(algo);
//     const char ss = ':';
//     vector<string> split;
//     splitStr(algo, ss, split);
//     for ( auto ss: split)
//     {
//         cout << ss << endl;
//     }

//     return 0;
// }
