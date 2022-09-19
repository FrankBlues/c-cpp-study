#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#include <tuple>
#include <bitset>
#include <regex>
#include <random>
#include <iomanip>

using namespace std;
using std::regex_constants::format_no_copy;

bool valid(const smatch& m)
{
    // if there is an open parenthesis before the area code
    if(m[1].matched)
        // the area code must be followed by a close parenthesis
        // and followed immediately by the rest of the number or a space
        return m[3].matched
            && (m[4].matched == 0 || m[4].str() == " ");
    else
        // then there can't be a close after the area code
        // the delimiters between the other two components must match
        return !m[3].matched
            && m[4].str() == m[6].str();
}

// almost surely the wrong way to generate a vector of random integers
// output from this function will be the same 100 numbers on every call!
vector<unsigned> bad_randVec()
{
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0,9);
    vector<unsigned> ret;
    for (size_t i = 0; i < 100; ++i)
        ret.push_back(u(e));
    return ret;
}

// returns a vector of 100 uniformly distributed random numbers
vector<unsigned> good_randVec()
{
    // because engines and distributions retain state, they usually should be
    // defined as static so that new numbers are generated on each call
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u(0,9);
    vector<unsigned> ret;
    for (size_t i = 0; i < 100; ++i)
        ret.push_back(u(e));
    return ret;
}

int main(int argc, char const *argv[])
{
    // Ex17.1.2
    tuple<int, int, int> tin(10, 20, 30);
    tuple<string, pair<string, int>> sptup;
    auto item = make_tuple("0-999-78345-X", 3, 20.00);
    auto i1 = get<0>(tin);
    size_t i2 = 0;

    bitset<32> bitvec(1U); // 32 bits; low-order bit is 1, remaining bits are 0
    // bitvec1 is smaller than the initializer; high-order bits from the initializer are discarded
    bitset<13> bitvec1 (0xbeef); // bits are 1111011101111
    // bitvec2 is larger than the initializer; high-order bits in bitvec2 are set to zero
    bitset<20> bitvec2(0xbeef); // bits are 00001011111011101111
    // on machines with 64-bit long long 0ULL is 64 bits of 0, so ~0ULL is 64 ones
    bitset<128> bitvec3(~0ULL); // bits 0 ... 63 are one; 63 ... 127 are zero

    bitset<32> bitvec4("1100"); // bits 2 and 3 are 1, all others are 0

    string str("1111111000000011001101");
    bitset<32> bitvec5(str, 5, 4); // four bits starting at str[5], 1100
    bitset<32> bitvec6(str, str.size()-4); // use last four characters

    // operations
    bool is_set = bitvec.any(); // true, one bit is set
    bool is_not_set = bitvec.none(); // false, one bit is set
    bool all_set = bitvec.all(); // false, only one bit is set
    size_t onBits = bitvec.count(); // returns 1
    size_t sz = bitvec.size(); // returns 32
    bitvec.flip(); // reverses the value of all the bits in bitvec
    bitvec.reset(); // sets all the bits to 0
    bitvec.set(); // sets all the bits to 1

    bitvec.flip(0); // reverses the value of the first bit
    bitvec.set(bitvec.size() - 1); // turns on the last bit
    bitvec.set(0, 0); // turns off the first bit
    bitvec.reset(i2); // turns off the ith bit
    bitvec.test(0); // returns false because the first bit is off

    bitvec[0] = 0; // turn off the bit at position 0
    bitvec[31] = bitvec[0]; // set the last bit to the same value as the first bit
    bitvec[0].flip(); // flip the value of the bit at position 0
    ~bitvec[0]; // equivalent operation; flips the bit at position 0
    bool b = bitvec[0]; // convert the value of bitvec[0] to bool

    unsigned long ulong = bitvec3.to_ulong();
    cout << "ulong = " << ulong << endl;

    bool status;
    // version using bitwise operators
    unsigned long quizA = 0; // this value is used as a collection of bits
    quizA |= 1UL << 27; // indicate student number 27 passed
    status = quizA & (1UL << 27); // check how student number 27 did
    quizA &= ~(1UL << 27); // student number 27 failed
    // equivalent actions using the bitset library
    bitset<30> quizB; // allocate one bit per student; all bits initialized to 0
    quizB.set(27); // indicate student number 27 passed
    status = quizB[27]; // check how student number 27 did
    quizB.reset(27); // student number 27 failed

    /// regex
    // find the characters ei that follow a character other than c
    string pattern("[^c]ei");
    // we want the whole word in which our pattern appears
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern, regex::icase); // construct a regex to find pattern
    smatch results; // define an object to hold the results of a search
    // define a string that has text that does and doesn't match pattern
    string test_str = "receipt freind theif receive";
    // use r to find a match to pattern in test_str
    if (regex_search(test_str, results, r)) // if there is a match
        cout << results.str() << endl; // print the matching word

    // it will repeatedly call regex_search to find all matches in file
    for (sregex_iterator it(test_str.begin(), test_str.end(), r), end_it;
        it != end_it; ++it)
        cout << it->str() << endl; // matched word

    // one or more alphanumeric characters followed by a '.' followed by "cpp" or "cxx" or "cc"
    regex r1("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase);  // () subexpressions
    smatch results1;
    string filename("xxxx.CC"); 
    if (regex_search(filename, results1, r1))
        cout << results1.str() << endl  // print the current match
             << results1.str(1) << endl;
    
    string phone = 
        "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
    regex r2(phone); // a regex to find our pattern
    smatch m;
    string s;
    // read each record from the input file
    // while (getline(cin, s))
    // {
    //     // for each matching phone number
    //     for(sregex_iterator it(s.begin(), s.end(), r2), end_it;
    //         it != end_it; ++it)
    //     {
    //         // check whether the number's formatting is valid
    //         if (valid(*it))
    //             cout << "valid: " << it->str() << endl;
    //         else
    //             cout << "not valid: " << it->str() << endl;
    //     }
    // }

    // regex replace
    string fmt = "$2.$5.$7"; // reformat numbers to ddd.ddd.dddd
    // read each record from the input file
    // morgan (201) 555-2368 862-555-0123
    // drew (973)555.0130
    // lee (609) 555-0132 2015550175 800.555-0000
    // while (getline(cin, s))
    //     cout << regex_replace(s, r2, fmt, format_no_copy) << endl;

    // random
    default_random_engine e; // generates random unsigned integers
    cout << "min: " << e.min() << " max: " << e.max() << endl;
    for (size_t i = 0; i < 10; ++i)
        // e() "calls" the object to produce the next random number
        cout << e() << " ";

    // uniformly distributed from 0 to 9 inclusive
    uniform_int_distribution<unsigned> u(0,9);
    // default_random_engine e; // generates unsigned random integers
    for (size_t i = 0; i < 10; ++i)
        // u uses e as a source of numbers
        // each call returns a uniformly distributed value in the specified range
        cout << u(e) << " ";

    // seed
    default_random_engine e1; // uses the default seed
    default_random_engine e2(2147483646); // use the given seed value
    // e3 and e4 will generate the same sequence because they use the same seed
    default_random_engine e3; // uses the default seed value
    e3.seed(32767); // call seed to set a new seed value
    default_random_engine e4(32767); // set the seed value to 32767

    default_random_engine e11(time(0)); // a somewhat random seed use time

    cout << endl;
    default_random_engine e111; // generates unsigned random integers
    // uniformly distributed from 0 to 1 inclusive
    uniform_real_distribution<double> u1(0,1);
    for (size_t i = 0; i < 10; ++i)
        cout << u1(e111) << " ";

    // empty <> signify we want to use the default result type
    uniform_real_distribution<> uuu(0,1); // generates double by default

    // default_random_engine e; // generates random integers
    normal_distribution<> n(4,1.5); // mean 4, standard deviation 1.5
    vector<unsigned> vals(9); // nine elements each 0
    for (size_t i = 0; i != 200; ++i) {
        unsigned v = lround(n(e)); // round to the nearest integer cmath
        if (v < vals.size()) // if this result is in range
            ++vals[v]; // count how often each number appears
    }

    for (size_t j = 0; j != vals.size(); ++j)
        cout << j << ": " << string(vals[j], '*') << endl;

    // bernoulli_distribution
    string resp;
    // default_random_engine e; // e has state, so it must be outside the loop!
    bernoulli_distribution bb; // 50/50 odds by default  bb(.55) 55/45 odd
    // do {
    //     bool first = bb(e); // if true, the program will go first
    //     cout << (first ? "We go first"
    //                 : "You get to go first") << endl;
    //     // play the game passing the indicator of who goes first
    //     // cout << ((play(first)) ? "sorry, you lost"
    //     //             : "congrats, you won") << endl;
    //     cout << "play again? Enter 'yes' or 'no'" << endl;
    // } while (cin >> resp && resp[0] == 'y');

    // IO
    cout << "default bool values: " << true << " " << false
        << "\nalpha bool values: " << boolalpha  // // sets the internal state of cout
        << true << " " << false << noboolalpha << endl;  // // resets the internal state to default formatting
    
    cout << showbase; // show the base when printing integral values
    cout << "default: " << 20 << " " << 1024 << endl;
    cout << "octal: " << oct << 20 << " " << 1024 << endl;
    cout << "hex: " << hex << 20 << " " << 1024 << endl;
    cout << "decimal: " << dec << 20 << " " << 1024 << endl;
    cout << noshowbase; // reset the state of the stream

    cout << uppercase << showbase << hex
        << "printed in hexadecimal: " << 20 << " " << 1024
        << nouppercase << noshowbase << dec << endl;

    // cout.precision reports the current precision value
    cout << "Precision: " << cout.precision()
        << ", Value: " << sqrt(2.0) << endl;
    // cout.precision(12) asks that 12 digits of precision be printed
    cout.precision(12);
    cout << "Precision: " << cout.precision()
        << ", Value: " << sqrt(2.0) << endl;
    // alternative way to set precision using the setprecision manipulator
    cout << setprecision(3);
    cout << "Precision: " << cout.precision()
        << ", Value: " << sqrt(157) << endl;

    cout << "default format: " << 100 * sqrt(2.0) << '\n'
        << "scientific: " << scientific << 100 * sqrt(2.0) <<
        '\n'
        << "fixed decimal: " << fixed << 100 * sqrt(2.0) <<
        '\n'
        << "hexadecimal: " << hexfloat << 100 * sqrt(2.0) <<
        '\n'
        << "use defaults: " << defaultfloat << 100 * sqrt(2.0)
        << "\n\n";
    
    cout << 10.0 << endl; // prints 10
    cout << showpoint << 10.0 // prints 10.0000
        << noshowpoint << endl; // revert to default format for the decimal point

    int i = -16;
    double d = 3.14159;
    // pad the first column to use a minimum of 12 positions in the output
    cout << "i: " << setw(12) << i << "next col" << '\n'
    << "d: " << setw(12) << d << "next col" << '\n';
    // pad the first column and left-justify all columns
    cout << left
    << "i: " << setw(12) << i << "next col" << '\n'
    << "d: " << setw(12) << d << "next col" << '\n'
    << right; // restore normal justification
    // pad the first column and right-justify all columns
    cout << right
    << "i: " << setw(12) << i << "next col" << '\n'
    << "d: " << setw(12) << d << "next col" << '\n';
    // pad the first column but put the padding internal to the field
    cout << internal
    << "i: " << setw(12) << i << "next col" << '\n'
    << "d: " << setw(12) << d << "next col" << '\n';
    // pad the first column, using # as the pad character
    cout << setfill('#')
        << "i: " << setw(12) << i << "next col" << '\n'
        << "d: " << setw(12) << d << "next col" << '\n'
        << setfill(' '); // restore the normal pad character
    
    // char ch;
    // cin >> noskipws; // set cin so that it reads whitespace
    // while (cin >> ch)
    //     cout << ch;
    // cin >> skipws; // reset cin to the default state so that it discards whitespace
    
    int ch; // use an int, not a char to hold the return from get()
    // loop to read and write all the data in the input
    // while ((ch = cin.get()) != EOF)
    //     cout.put(ch);
    

    // open for input and output and preposition file pointers to end-of-file
    // file mode argument see § 8.4 (p. 319)
    fstream inOut("copyOut",
                        fstream::ate | fstream::in | fstream::out);
    if (!inOut) {
        cerr << "Unable to open file!" << endl;
        return EXIT_FAILURE; // EXIT_FAILURE see § 6.3.2 (p. 227)
    }
    // inOut is opened in ate mode, so it starts out positioned at the end
    auto end_mark = inOut.tellg();// remember original end-of-file position
    inOut.seekg(0, fstream::beg); // reposition to the start of the file
    size_t cnt = 0; // accumulator for the byte count
    string line; // hold each line of input
    // while we haven't hit an error and are still reading the original data
    while (inOut && inOut.tellg() != end_mark
            && getline(inOut, line)) { // and can get another line of input
        cnt += line.size() + 1; // add 1 to account for the newline
        auto mark = inOut.tellg(); // remember the read position
        inOut.seekp(0, fstream::end); // set the write marker to the end
        inOut << cnt; // write the accumulated length
        // print a separator if this is not the last line
        if (mark != end_mark) inOut << " ";
        inOut.seekg(mark); // restore the read position
    }
    inOut.seekp(0, fstream::end); // seek to the end
    inOut << "\n"; // write a newline at end-offile                                                                                                                             
    return 0;
}
