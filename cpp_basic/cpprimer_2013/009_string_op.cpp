#include <iostream>
#include <string>
using std::string;

using namespace std;

int main()
{
    string word, line; // 默认初始化， 空字符串
    // while (cin >> word)
    while (getline(cin, line))
    {
        if (!line.empty())
            cout << line << endl;
        if (!line.size() > 80)
            cout << line << endl;
        
        for(auto &c : line)
            if (!ispunct(c))
                cout << c;
        cout << endl;
        cout << line << endl;


        // toupper
        line[0] = toupper(line[0]);
        cout << line << endl;
        for(decltype(line.size()) index = 0;
            index != line.size() && !isspace(line[index]); ++ index)
            line[index] = toupper(line[index]);  // upper first word
        cout << line << endl;
    }
    cout << endl;
		
	
    return 0;
}