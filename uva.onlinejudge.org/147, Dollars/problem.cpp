#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
  double f;
  int a;
  const int N = 11;
  int c[N] = { 10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5 };
  while (true) {
    cin >> f;
    int a = f * 100.0 + 0.1E-9;
    if (a == 0) break;
    vector<long long> s(30001, 0);
    s[0] = 1;
    for (int i = 0; i < N; ++i) {
      int coin = c[i];
      for (int j = coin; j <= a; ++j) {
        s[j] += s[j - coin];
      }
    }
    printf("%6.2f%17lld\n", f, s[a]);
  }
  return 0;
}
