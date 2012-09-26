#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
  ifstream is("INPUT.TXT");
  ofstream os("OUTPUT.TXT");
  string s; is >> s;
  int N = s.length();
  vector<vector<int> > dp(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i) dp[i][i] = 1;
  for (int t = 1; t < N; ++t) {
    for (int i = 0; i < N - t; ++i) {
      int j = i + t;
      dp[i][j] = dp[i + 1][j] + dp[i][j - 1];
      dp[i][j] += s[i] == s[j] ? 1 : -dp[i + 1][j - 1];
    }
  }
  os << dp[0][N - 1] << endl;
  return 0;
}

