// Author: Diego Alejandro Restrepo S.
// Copyright 2011 www.github.com/Diegores14/HPC
//
#include <mpi.h>
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

long long simulation(int l, int L, long long cant) {
    long long cantOverLaps = 0;
    #pragma omp parallel for num_threads(8) reduction(+:cantOverLaps)
    for(long long i = 0; i < cant; i++) {
        long double x, theta;
        x = distribution(generator) * l;
        theta = distribution(generator) * PI;
        if(validation(l, L, x, (theta))) {
            cantOverLaps++;
        }
    }
    return cantOverLaps;
}

int main(int argc, char** argv) {
    
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    long long it = atoll(argv[1]);
    
    // start Time
    long double start = MPI_Wtime();

    // Master
    if(world_rank == 0) {
      long long aux, l = 30, L = 10;
      long long cantOverLaps = simulation(30, 10, (it+3)/4);
      MPI_Recv(&aux, 1, MPI_LONG_LONG, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      cantOverLaps += aux;
      MPI_Recv(&aux, 1, MPI_LONG_LONG, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      cantOverLaps += aux;
      MPI_Recv(&aux, 1, MPI_LONG_LONG, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      cantOverLaps += aux;
      long double ans = (long double)((1LL*it*2*L))/(1LL * cantOverLaps * l);
      cout << fixed << setprecision(8) << it << ',' << abs(PI - ans) << ',';
      cout << MPI_Wtime() - start << '\n';
    }

    // Workers
    if(world_rank == 1) {
      long long aux = simulation(30, 10, (it+3)/4);
      MPI_Send(&aux, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }
    if(world_rank == 2) {
      long long aux = simulation(30, 10, (it+3)/4);
      MPI_Send(&aux, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }
    if(world_rank == 3) {
      long long aux = simulation(30, 10, (it+3)/4);
      MPI_Send(&aux, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
    return 0;
}