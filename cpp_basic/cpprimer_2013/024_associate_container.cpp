#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

#include <string>
#include <cstring>
#include <vector>
#include <list>

#include <utility>

using namespace std;


void excise113()
{
    map<string, size_t> wc;
    set<string> exlude{"the", "an", "a", "but"};
    string s;
    
    while (cin >> s)
    {
        if (exlude.find(s) == exlude.end())
            ++wc[s];
    }

    for(const auto &w: wc)
    {
        cout << w.first << " occurs:" << w.second << endl;
    }
}

void excise1110()
{
    map<string, list<int>> words_line;
    map<vector<int>::iterator, int> iter2int_vec;  // ok
    map<list<int>::iterator, int> iter2int_lst;  // cannot
    vector<int> ivec = {1, 2, 3};
    list<int> ilst(ivec.begin(), ivec.end());

    for(auto beg = ivec.begin(); beg != ivec.end(); ++beg)
        iter2int_vec[beg] = *beg;
}

void excise1112()
{
    vector<pair<string, int>> pvec;
    string s;
    int i;
    while (cin >> s >> i)
    {
        
        pvec.push_back({s, i});
        pvec.push_back(make_pair(s, i));
        pvec.push_back(pair<string, int>(s, i));
    }
    
}

/// print use iter
void excise1118()
{
    map<string, size_t> wc;
    set<string> exlude{"the", "an", "a", "but"};
    string s;
    
    while (cin >> s)
    {
        if (exlude.find(s) == exlude.end())
            ++wc[s];
    }

    // for(const auto &w: wc)
    // {
    //     cout << w.first << " occurs:" << w.second << endl;
    // }
    map<string, size_t>::const_iterator map_iter = wc.cbegin();
    while(map_iter != wc.cend())
    {
        cout << map_iter->first << " occurs:" << map_iter->second << endl;
        ++map_iter;
    }
}

/// user inserter
void excise1120()
{
    map<string, size_t> wc;
    set<string> exlude{"the", "an", "a", "but"};
    string s;
    
    while (cin >> s)
    {
        if (exlude.find(s) == exlude.end())
        {
            pair<map<string, size_t>::iterator, bool> inserter = wc.insert({s, 1});
            if (!inserter.second)
                ++inserter.first->second;
        }
            
    }

    map<string, size_t>::const_iterator map_iter = wc.cbegin();
    while(map_iter != wc.cend())
    {
        cout << map_iter->first << " occurs:" << map_iter->second << endl;
        ++map_iter;
    }
}

/// user inserter
void excise1131()
{
    multimap<string, string> works = {{"jinyong", "shediao"},
                                      {"luxun", "nahan"},
                                      {"jinyong", "shendiao"},
                                      {"luxun", "huajian"},
                                      {"jinyong", "tianlong"},
                                      {"luoguanzhong", "sanguo"}};
    string key("luxun");
    auto iter = works.find(key);
    // size_t count = works.count(key);
    // while (count)
    // {
    //     cout << iter -> second << endl;
    //     ++iter;
    //     --count;
    // }
    auto lower = works.lower_bound(key);  // 用upper lower打印同一key
    while (lower != works.upper_bound(key))
    {
        cout << (lower++) -> second << endl;
    }
    
    if (iter != works.end())
        works.erase(key);  // 删除指定
    for(const auto &w: works)
        cout << w.first << ":" << w.second << endl;
}

void excise1133()
{

}
map<string, string> buildMap(ifstream &);
const string &
transform(const string &, const map<string, string> &);
void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file); // store the transformations
    string text; // hold each line from the input
    while (getline(input, text)) { // read a line of input
        istringstream stream(text); // read each word
        string word;
        bool firstword = true; // controls whether a space is printed
        while (stream >> word) {
            if (firstword)
                firstword = false;
            else
                cout << " "; // print a space between words
            // transform returns its first argument or its transformation
            cout << transform(word, trans_map); // print the output
        }
        cout << endl; // done with this line of input
    }
}

map<string, string> buildMap(ifstream &map_file)
{
    map<string, string> trans_map; // holds the transformations
    string key; // a word to transform
    string value; // phrase to use instead
    // read the first word into key and the rest of the line into value
    while (map_file >> key && getline(map_file, value))
    {
        if (value.size() > 1) // check that there is a transformation
            trans_map[key] = value.substr(1); // skip leading space
        else
            throw runtime_error("no rule for " + key);
    }
    return trans_map;
}


const string &
transform(const string &s, const map<string, string> &m)
{
    // the actual map work; this part is the heart of the program
    auto map_it = m.find(s);
    // if this word is in the transformation map
    if (map_it != m.cend())
        return map_it->second; // use the replacement word
    else
        return s; // otherwise return the original unchanged
}

int main()
{
    // excise113();
    // excise1110();
    // excise1118();
    // excise1120();
    // excise1131();
    string mapfile("./mapfile.txt");
    ifstream map_file(mapfile);
    string transfile("./transform.txt");
    ifstream trans_file(transfile);
    word_transform(map_file, trans_file);

    cout << hash<string>()(mapfile) << endl; 

    return 0;
}