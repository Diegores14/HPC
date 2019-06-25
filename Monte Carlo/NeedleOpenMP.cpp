#include <bits/stdc++.h>
using namespace std;
#include <omp.h>
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
    #pragma omp parallel for num_threads(8) reduction(+:cantOverLaps)
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
    long long it = atoll(argv[1]);
    long double start = omp_get_wtime();
    cout << fixed << setprecision(8) << it << ',' << abs(PI - simulation(30, 10, it)) << ',';
    cout << omp_get_wtime() - start << '\n';
    return 0;
}