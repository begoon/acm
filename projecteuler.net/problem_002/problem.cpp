#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N = 4000000;
  int a = 1;
  int b = 2;
  __int64 r = 2;
  while (true) {
    int n = a + b;
    if (n > N) break;
    if ((n & 1) == 0) {
      r += n;
    a = b;
    b = n;
  }
  cout << r << endl;
  return 0;
}

