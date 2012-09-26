#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
  freopen("INPUT.TXT", "r", stdin);
  freopen("OUTPUT.TXT", "w", stdout);
  int N; cin >> N;
  vector<vector<int> > f(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int v; cin >> v;
      for (int t = 0; t < N; ++t) {
        if (t == i) continue;
        f[t][j] += v;
      }
    }
  }
#if 0
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cout << f[i][j] << " ";
    cout << endl;
  }
#endif
  vector<int> g(N);
  for (int i = 0; i < N; ++i) g[i] = i;
  int best = numeric_limits<int>::max();
  string h(N, '?');
  do {
    int r = 0;
    for (int i = 0; i < N; ++i)
      r += f[i][g[i]];
    if (r < best) {
      best = r;
      for (int i = 0; i < N; ++i)
        h[i] = 'A' + g[i];
    }
  } while (next_permutation(g.begin(), g.end()));
  cout << h << endl;
  cout << best << endl;
  return 0;
}
