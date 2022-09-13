#ifndef ORQUERY_H
#define ORQUERY_H

#include "BinaryQuery.h"
#include "Query.h"
#include "QueryResult.h"

class OrQuery: public BinaryQuery
{
    friend Query operator| (const Query&, const Query&);
    OrQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "|"){}
    // concrete class: OrQuery inherits rep and defines the remaining pure virtual
    QueryResult eval(const TextQuery&) const;
};

inline Query operator| (const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}


#endif