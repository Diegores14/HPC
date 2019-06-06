#include <bits/stdc++.h>
using namespace std;
long double PI = acos(-1);
typedef long long LL;

bool validation(int l, int L, LL x, long double theta) {
    return (l <= x + (L/2)*sin(theta)) || (x - (L/2)*sin(theta) <= 0);
}

long double simulation(int l, int L, int cant) {
    int cantOverLaps = 0;
    //set<LL> s1, s2;
    LL x, theta;
    for(int i = 0; i < cant; i++) {
        x = rand()%l;
        theta = rand()%LL(PI*100000000);
        if(validation(l, L, x, (long double)(theta)/100000000)) {
            cantOverLaps++;
        }
    }
    return (long double)((1LL*cant*2*L))/(1LL * cantOverLaps * l);
}

int main() {
    srand(time(NULL));
    cout << fixed << setprecision(4) << simulation(30, 10, 10000000) << '\n';
    return 0;
}