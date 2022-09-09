#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Quote.h"
#include "Bulk_quote.h"
#include "TextQuery.h"
#include "QueryResult.h"


using namespace std;

double print_total(std::ostream &os, const Quote &item, std::size_t n);

void runQueries(ifstream &infile)
{
    // infile is an ifstream that is the file we want to query
    TextQuery tq(infile); // store the file and build the query map
    // iterate with the user: prompt for a word to find and print results
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        // stop if we hit end-of-file on the input or if a 'q' is entered
        if (!(cin >> s) || s == "q") break;
        // run the query and print the results
        print(cout, tq.query(s)) << endl;
    }
}

int main(int argc, char const *argv[])
{
    // ex15.6
    Quote q("textbook", 10.60);
    Bulk_quote bq("textbook", 10.60, 15, 0.3);

    // print_total(std::cout, q, 12);
    // print_total(std::cout, bq, 12);

    // exercise 1511
    // q.print_mem(cout);
    // cout << endl;
    // bq.print_mem(cout);

    // exercise1526
    // Bulk_quote bq1 = bq;
    // Bulk_quote bq2(bq);
    // Quote q1(bq);

    // ex1528
    // vector<Quote> qvec;
    // vector<shared_ptr<Quote>> sqvec;
    // qvec.push_back(q);
    // qvec.push_back(bq);
    // // same
    // cout << qvec[0].net_price(15) << endl;
    // cout << qvec[1].net_price(15) << endl;  //print only the base part
    // ex1529  
    // sqvec.push_back(make_shared<Quote>("textbook", 10.60));
    // sqvec.push_back(make_shared<Bulk_quote>("textbook", 10.60, 15, 0.3));
    // cout << sqvec[0]->net_price(15) << endl;
    // cout << sqvec[1]->net_price(15) << endl; // print the derived part

    auto is = ifstream("./spa.txt");
    runQueries(is);

    return 0;
}

double print_total(std::ostream &os, const Quote &item, std::size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn()
       << "# sold: " << n << " total due: " << ret << std::endl;
    return ret;
}


