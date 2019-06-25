#include <bits/stdc++.h>
using namespace std;


int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0, 1000);
    if(argc == 2){
        int n = atoi(argv[1]);
        cout << "Some random numbers between 0, and " << n << '\n';
        for(int i = 0; i < n; i++) {
            //cout << distribution(generator) << '\n';
        }
    } else {
        cout << "Ponga la cantidad de iteraciones como argumento\n";
    }
    return 0;
}