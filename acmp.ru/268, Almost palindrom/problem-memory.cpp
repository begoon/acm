#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int main(int argc, char* argv[]) {
  freopen("INPUT.TXT", "r", stdin);
  freopen("OUTPUT.TXT", "w", stdout);
  
  int N, K;
  string s;
  cin >> N >> K >> s; 

  int r = 0;
  vector<vector<int> > dp(N, vector<int>(N, 0));
  for (int t = 1; t < N; ++t) {
    for (int i = 0; i < N - t; ++i) {
      int j = i + t;
      dp[i][j] = dp[i + 1][j - 1];
      if (s[i] != s[j])
        dp[i][j] += 1;
      if (dp[i][j] <= K)
        r += 1;
    }
  }

  cout << r + N << endl;

  return 0;
}
