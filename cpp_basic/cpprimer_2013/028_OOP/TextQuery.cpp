#include "TextQuery.h"
#include "QueryResult.h"

using std::string;

TextQuery::TextQuery(std::ifstream &is): file(new std::vector<string>)
{
    string text;
    while (getline(is, text))  // for each line in the file
    {
        file -> push_back(text);  // remember this line of text
        int n = file->size() - 1;  // the current line number
        std::istringstream line(text);  // separate the line into words
        string word;
        while (line >> word)  // for each word in that line
        {
            // if word isn't already in wm, subscripting adds a new entry
            auto &lines = wm[word]; // lines is a shared_ptr
            if (!lines) // that pointer is null the first time we see word
            {
                lines.reset(new std::set<line_no>); // allocate a new set   
            }
            lines->insert(n); // insert this line number
        }

    }

}

QueryResult TextQuery::query(const std::string &sought) const
{
    // we'll return a pointer to this set if we don't find sought
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file); // not found
    else
        return QueryResult(sought, loc->second, file);

}

TextQuery::~TextQuery()
{
}