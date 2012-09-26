#include <iostream>
#include <vector>
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
  vector<int> colors(N, 0);
  for (int i = 0; i < N; ++i)
    cin >> colors[i];
  int bad = 0;
  for (int i = 0; i < N; ++i)
    for (int j = i + 1; j < N; ++j)
      if (g[i][j])
        if (colors[i] != colors[j])
          bad += 1;
  cout << bad << endl;
  return 0;
}
