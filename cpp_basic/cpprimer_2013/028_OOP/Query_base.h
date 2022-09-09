#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include "TextQuery.h"
#include "QueryResult.h"

class Query_base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no; // used in the eval functions
    virtual ~Query_base() = default;
private:
    // eval returns the QueryResult that matches this Query
    virtual QueryResult eval(const TextQuery&) const = 0;
    // rep is a string representation of the query
    virtual std::string rep() const = 0;
};

#endif