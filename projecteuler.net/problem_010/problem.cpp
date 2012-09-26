#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N = 2000000;
  vector<bool> p(N + 1, true);
  for (int i = 2; i*i <= N; ++i) {
    if (!p[i]) continue;
    for (int j = i*i; j <= N; j += i)
      p[j] = false;    
  }
  __int64 r = 0;
  for (int i = 2; i <= N; i++)
    if (p[i])
      r += i;
  cout << r << endl;
  return 0;
}

