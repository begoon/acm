#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int N, K;

int main(int argc, char* argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  cin >> N >> K;

  if (N > K) {
    cout << 0 << endl;
    return 0;
  }

  vector<int> c(K, 0);
  c[0] = 1;

  for (int k = 1; k < K; ++k) {
    for (int i = k; i >= 0; --i) {
      if ((k & 1) != (i & 1)) continue;
      c[i] = 0;
      if (i > 0) c[i] += c[i - 1];
      if (i < k) c[i] += c[i + 1];
    }
  }
  cout << c[N - 1] << endl;
  return 0;
}
