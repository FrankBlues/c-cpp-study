#include <iostream>
#include <fstream>
#include <vector>

#include <new>

#include "StrBlob.h"
#include "TextQuery.h"
#include "QueryResult.h"

using namespace std;

void excise121()
{
    StrBlob b1;
    {
    StrBlob b2 = {"a", "an", "the"};
    b1 = b2;
    b2.push_back("about");
    }

    cout << b1.size() << endl;  // 4
    // cout << b2.size() << endl;  // undefined
}

vector<int> * exercise126()
{
    return new vector<int>();
}


vector<int> * exercise126_1()
{
    vector<int> *ivec = exercise126();
    int i;
    while (cin >> i)
    {
        (*ivec).push_back(i);
    }
    return ivec;
}

void exercise126_2()
{
    vector<int> *ivec = exercise126_1();
    for (const auto &i: *ivec)
    {
        cout << i << " ";
    }
    cout << endl;
    delete ivec;
}

shared_ptr<vector<int>> exercise127()
{
    return make_shared<vector<int>>();
}

shared_ptr<vector<int>> exercise127_1()
{
    auto ivec = exercise127();
    int i;
    while (cin >> i)
    {
        (*ivec).push_back(i);
    }
    return ivec;
}

void exercise127_2()
{
    auto ivec = exercise127_1();
    for (const auto &i: *ivec)
    {
        cout << i << " ";
    }
    cout << endl;
}

void exercise1220()
{
    StrBlob sb;
    ifstream in_f("./exer1220.txt");
    string s;
    while(getline(in_f, s))
        sb.push_back(s);
    
    auto sz = sb.size();
    StrBlobPtr beg(sb.begin());
    for(decltype(sz) i = 0; i < sz; ++i)
    {
        cout << beg.deref() << endl;
        beg.incr();
    }
}

void exercise1223()
{
    string s1("aaa");
    string s2("bbb");
    auto sz = s1.size() + s2.size();
    char *pc = new char[sz];
    for (decltype(sz) i = 0; i < sz; ++i)
        if (i < s1.size())
            *(pc + i) = s1[i];
        else
            *(pc + i) = s2[i - s1.size()];
    
    for (decltype(sz) i = 0; i < sz; ++i)
        cout << *(pc + i);
    cout << endl;

    delete [] pc;

    cout << s1 + s2 << endl;
}

// void allocator()
// {
//     int n = 20;
//     allocator<string> alloc; // object that can allocate strings
//     auto const p = alloc.allocate(n); // allocate n unconstructed strings

//     auto q = p; // q will point to one past the last constructed element
//     alloc.construct(q++); // *q is the empty string
//     alloc.construct(q++, 10, 'c'); // *q is cccccccccc
//     alloc.construct(q++, "hi"); // *q is hi!

//     cout << *(p+2) << endl;  // p+1 cccccccccc  p+2 hi
//     cout << p << endl << q << endl;

//     while (q != p)
//         alloc.destroy(--q); // free the strings we actually allocated

//     alloc.deallocate(p, n);

//     // construct elements starting at p as copies of elements in vi
//     vector<string> svec{"aa", "bb", "cc"};
//     auto p1 = uninitialized_copy(svec.begin(), svec.end(), p);
//     // initialize the remaining elements
//     uninitialized_fill_n(p1, svec.size(), "dd");
// }

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
    // exercise126_2();
    // exercise127_2();
    // exercise1220();
    // exercise1223();

    auto is = ifstream("./spa.txt");
    runQueries(is);

    


    return 0;
}

