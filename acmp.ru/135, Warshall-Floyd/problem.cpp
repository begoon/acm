#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

const int huge = 100 * 100 * 2;
int main(int argc, char* argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int N; cin >> N;
  vector<vector<int> > w(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      cin >> w[i][j];
  for (int k = 0; k < N; ++k)
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; ++j) {
      if (j > 0) cout << " ";
      cout << w[i][j];
    }
    cout << endl;
  }
  return 0;
}
