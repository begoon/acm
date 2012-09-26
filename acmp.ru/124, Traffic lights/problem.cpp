#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int N, M; cin >> N >> M;
  vector<int> r(N, 0);
  for (int i = 0; i < M; ++i) {
    int a, b; cin >> a >> b;
    r[a - 1] += 1;
    r[b - 1] += 1;
  }
  for (int i = 0; i < N; ++i) {
    if (i > 0) cout << " ";
    cout << r[i];
  }
  cout << endl;
  return 0;
}
