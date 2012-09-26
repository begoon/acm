#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int N; cin >> N;
  vector<vector<int> > g(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      cin >> g[i][j];
  int from, to; cin >> from >> to;
  from -= 1;
  to -= 1;
  vector<bool> visited(N, false);
  queue<pair<int, int> > q;
  q.push(make_pair(from, 0));
  while (!q.empty()) {
    pair<int, int> t = q.front();
    q.pop();
    visited[t.first] = true;
    if (t.first == to) {
      cout << t.second << endl;
      return 0;
    }
    for (int i = 0; i < N; ++i)
      if (!visited[i] && g[t.first][i])
        q.push(make_pair(i, t.second + 1));
  }
  cout << -1 << endl;
  return 0;
}
