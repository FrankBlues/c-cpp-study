#include <iostream>
#include <string>
#include <vector>
using std::string;

using namespace std;

int main()
{
    // process the vector and change each word to uppercase. Print the 
    // transformed elements, eight words to a line.
    string word; // 默认初始化， 空字符串
    vector<string> words;
    while (cin >> word)
    {
        words.push_back(word);
    }

    decltype(words.size()) index = 0;
    for(auto &w: words)
    {
        for (auto &s: w)
            s = toupper(s);
        cout << w << " ";
        ++index;
        if (index != 0 && index % 8 == 0)
            cout << endl;
    }
    
    cout << endl;

    vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Print the sum of each pair of adjacent elements
    for(decltype(nums.size()) index = 0; index < nums.size(); index += 2)
    {
        if (index + 1 >= nums.size())
            cout << nums[index];
        else
            cout << nums[index] + nums[index + 1] << " ";
    }    

	cout << endl;
    // prints the sum of the first and last elements, followed by the sum of 
    // the second and second-to-last,and so on
    for(decltype(nums.size()) index = 0; index < nums.size()/2; index += 1)
        cout << nums[index] + nums[nums.size() - 1 - index] << " ";
    cout << endl;
	
    return 0;
}