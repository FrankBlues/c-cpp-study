#include <iostream>

#include <vector>
using std::vector;

vector<int> prime(unsigned int nb_primes){
    int n;
    bool m = false;
    vector<int> p;
    n = 2;
    while (n < nb_primes){
        m = true;
        for (auto i : p){
            if (n % i == 0){
                m = false;
                break;
            } 
        }
        if (m)
            p.push_back(n);
        n += 1;
    }
    return p;
}

int main(int argc, char const *argv[])
{
    unsigned int nb_primes = 200000;
    vector<int> p = prime(nb_primes);

    for (auto i : p){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}
