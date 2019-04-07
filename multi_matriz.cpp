#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
typedef vector<int> vi;
int n;

vector< vi > multiplication(vector< vi> & m1, vector< vi > & m2) {
  vector< vi > ans(n, vi(n, 0));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      for(int k=0; k<n; k++) {
        ans[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }
  return ans;
}

void print(vector< vi > m) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cout << m[i][j] << ' ';
    }
    cout << '\n';
  }
}

void generate(vector< vi > &m) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      m[i][j] = rand() % 10;
    }
  }
}

int main() {
  cin >> n;
  vector< vi > m1(n, vi(n)), m2(n, vi(n));
  srand (time(NULL));
  generate(m1);
  generate(m2);
  vector< vi > ans = multiplication(m1, m2);
  cout << "M1:\n";
  print(m1);
  cout << "M2:\n";
  print(m2);
  cout << "answer:\n";
  print(ans);
  return 0;
}
