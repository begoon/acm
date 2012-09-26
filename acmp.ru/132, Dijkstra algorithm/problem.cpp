#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;

const int huge = 100 * 100 + 1;

int main(int argc, char* argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int N, from, to; cin >> N >> from >> to;
  from -= 1;
  to -= 1;

  if (N == 1 || to == from) {
    cout << 0 << endl;
    return 0;
  }

  vector<vector<int> > g(N, vector<int>(N, 0));

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      cin >> g[i][j];

  vector<int> d(N, huge);
  d[from] = 0;
  vector<bool> done(N, false);
  vector<int> p(N, -1);

  while (1) {
    int min_dist = huge;
    int v = -1;
    for (int i = 0; i < N; ++i) if (!done[i]) {
      if (d[i] >= min_dist) continue;
      min_dist = d[i];
      v = i;
    }
    if (v == -1) break;
    done[v] = true;
    for (int i = 0; i < N; ++i) if (!done[i]) {
      if (g[v][i] < 0) continue;
      if (d[i] > d[v] + g[v][i]) {
        d[i] = d[v] + g[v][i];
        p[i] = v;
      }
    }
  }

  if (p[to] == -1) {
    cout << -1 << endl;
  } else {
    int r = 0;
    while (p[to] != -1) {
      r += g[p[to]][to];
      to = p[to];
    }
    cout << r << endl;
  }

  return 0;
}

