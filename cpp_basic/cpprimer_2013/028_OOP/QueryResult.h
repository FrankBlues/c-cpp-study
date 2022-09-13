#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <memory>

class QueryResult
{
    // friend std::ostream &print(std::ostream &, const QueryResult &);
    friend std::ostream& operator<<(std::ostream&, const QueryResult&);

public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) {}
    std::set<line_no>::iterator begin() const{return lines->begin();}
    std::set<line_no>::iterator end() const {return lines->end();}
    std::shared_ptr<std::vector<std::string>> get_file() const {return file;}
    
    ~QueryResult() {}

private:
    std::string sought;                             // word this query represents
    std::shared_ptr<std::set<line_no>> lines;       // lines it's on
    std::shared_ptr<std::vector<std::string>> file; // input file
};

inline
std::ostream& operator<<(std::ostream &os, const QueryResult &qr)
{
    // if the word was found, print the count and all occurrences
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << qr.lines->size() << " time(s)" << std::endl;
    // print each line in which the word appeared
    for (auto num : *qr.lines) // for every element in the set
        // don't confound the user with text lines starting at 0
        os << "\t(line " << num + 1 << ") "
        << *(qr.file->begin() + num) << std::endl;
    return os;
}

#endif