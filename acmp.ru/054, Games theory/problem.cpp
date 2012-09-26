#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int main(int argc, char* argv[]) {
  freopen("INPUT.TXT", "r", stdin);
  freopen("OUTPUT.TXT", "w", stdout);
  int N, M; cin >> N >> M;
  vector<vector<int> > f(N, vector<int>(M, 0));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      cin >> f[i][j];
  int upper = -2000;
  for (int i = 0; i < N; ++i) {
    int col_min = +2000;
    for (int j = 0; j < M; ++j)
      col_min = min(col_min, f[i][j]);
    upper = max(upper, col_min);
  }
  cout << upper << endl;
  int lower = +2000;
  for (int j = 0; j < M; ++j) {
    int row_max = -2000;
    for (int i = 0; i < N; ++i)
      row_max = max(row_max, f[i][j]);
    lower = min(lower, row_max);
  }
  cout << lower << endl;
}
