#include <iostream>
using namespace std;

int f(int n, int d) {
  int p = n / d;
  return d*(p*(p-1))/2;
}

int main() {
  int N = 1000 - 1;
  cout << f(N, 3) + f(N, 5) - f(N, 15) << endl;
  return 0;
}

