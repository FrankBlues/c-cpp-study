#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>

const char *getDriverName(const char *fileName);

void splitStr(const std::string &str, const char &c, std::vector<std::string> &res);

#endif