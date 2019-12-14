#include <iostream>

using namespace std;

const int Cities = 4;
const int Years = 2;
int main(){

    const char * cities[Cities] = {
        "city A","City B","City C","City D"
    };

    int maxtemps[Years][Cities] = {
        {23,45,12,90},
        {43,69,72,540}
    };

    for (int year = 0; year < Years ; ++year){
        cout << cities[year] << " : ";
        for (int city = 0 ; city < Cities ; ++city){
            cout << maxtemps[year][city] << "\t";
        }
        cout << endl;
        
    }
    cout << endl;

    return 0;
}