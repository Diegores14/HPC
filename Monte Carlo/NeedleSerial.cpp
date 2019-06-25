#include <bits/stdc++.h>
using namespace std;
long double PI = acos(-1);
typedef long long LL;
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
uniform_real_distribution<long double> distribution(0, 1);

bool validation(int l, int L, long double x, long double theta) {
    return (l <= x + (L/2)*sin(theta)) || (x - (L/2)*sin(theta) <= 0);
}

long double simulation(int l, int L, long long cant) {
    int cantOverLaps = 0;
    for(long long i = 0; i < cant; i++) {
        long double x, theta;
        x = distribution(generator) * l;
        theta = distribution(generator) * PI;
        if(validation(l, L, x, (theta))) {
            cantOverLaps++;
        }
    }
    return (long double)((1LL*cant*2*L))/(1LL * cantOverLaps * l);
}

int main(int argc, char *argv[]) {
    long long it = atoi(argv[1]);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    cout << fixed << setprecision(8) << it << ',' << abs(PI - simulation(30, 10, it)) << ',';
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> duracion = end - start;
    cout << duracion.count() << '\n';
    return 0;
}