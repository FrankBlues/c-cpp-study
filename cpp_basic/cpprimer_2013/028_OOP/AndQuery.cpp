#include <algorithm>
#include "AndQuery.h"

QueryResult AndQuery::eval(const TextQuery &text) const
{
    // virtual calls through the Query Query operands to get result sets for the operands
    auto right = rhs.eval(text), left = lhs.eval(text);
    // set to hold the intersection of left and right
    auto ret_lines = std::make_shared<std::set<line_no>>();
    // writes the intersection of two ranges to a destination iterator
    // destination iterator in this call adds elements to ret
    set_intersection(left.begin(), left.end(),
                     right.begin(), right.end(),
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}