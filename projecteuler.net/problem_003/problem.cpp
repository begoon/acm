#include <iostream>
#include <vector>
using namespace std;

int main() {
  __int64 N = 600851475143;
  __int64 i;
  for (i = 2; i*i <= N; ++i) {
    while (N % i == 0)
      N /= i;
  }
  if (N > 1)
    i = N;
  cout << i << endl;
  return 0;
}

