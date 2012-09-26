#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

int min(int a, int b) { return a < b ? a : b; }

int main(int argc, char* argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int N, M; cin >> N >> M;
  vector<vector<int> > g(N, vector<int>(N, 30000));
  for (int i = 0; i < M; ++i) {
     int a, b, w; cin >> a >> b >> w;
     g[a - 1][b - 1] = min(w, g[a - 1][b - 1]);
  }

  for (int i = 0; i < N; ++i) g[i][i] = 0;

  vector<int> d(N, 30000);
  d[0] = 0;

  for (int t = 0; t < N - 1; ++t)
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        if (g[j][i] != 30000 && d[j] != 30000)
          if (d[i] > d[j] + g[j][i])
            d[i] = d[j] + g[j][i];

  for (int i = 0; i < N; ++i) {
    if (i > 0) cout << " ";
    cout << d[i];
  }
  cout << endl;
    
  return 0;
}
