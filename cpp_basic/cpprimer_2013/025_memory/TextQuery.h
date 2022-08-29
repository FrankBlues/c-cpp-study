#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

class QueryResult;

class TextQuery
{
    friend class QueryResult;

public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream &);
    QueryResult query(const std::string &) const;
    ~TextQuery();

private:
    std::shared_ptr<std::vector<std::string>> file; // input file
    std::map<std::string,
             std::shared_ptr<std::set<line_no>>> wm;
};

#endif