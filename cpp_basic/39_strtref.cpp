//define and using a reference
#include <iostream>

using namespace std;

struct sysop{
    char name[26];
    char quote[64];
    int used;
};

const sysop & use(sysop & sysopred); //function with a reference turn type

int main(){
    sysop looper = {
        "Rick\"Fortran\"Looper",
        "I'm a qoto kind of guy.",
        0
    };

    use(looper);
    cout << "Looper: " << looper.used << " use(s)\n";
    cout << "Copycat: " << looper.used << " use(s)\n";
    cout << "use(looper): " << use(looper).used << " use(s)\n";
    
    return 0;
}
// use () return the reference passed to it
const sysop & use(sysop & sysopred){
    cout << sysopred.name << " says:\n";
    cout << sysopred.quote << endl;
    sysopred.used++;
    return sysopred;
}
