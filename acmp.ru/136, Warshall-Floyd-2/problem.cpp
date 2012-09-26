#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

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
      for (int j = 0; j < N; ++j) {
         if (w[i][k] == -1 || w[k][j] == -1) continue;
         if (w[i][j] == -1)
           w[i][j] = w[i][k] + w[k][j];
         else
           w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
      }
  int r = -1;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      r = max(r, w[i][j]);
 
  cout << r << endl;
  return 0;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)
      cout << w[i][j] << " ";
    cout << endl;
  }
}
