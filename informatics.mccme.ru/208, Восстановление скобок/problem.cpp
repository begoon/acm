#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

//    0 1 2 3 4 5 6 7
// 0  1 x x x x x x x
// 1  0 1 x x x x x x
// 2  1 x 1 x x x x x
// 3  x 2 x 1 x x x x
// 4  2 x 3 x 1 x x x
// 5  x 5 x 4 x 1 x x
// 6  x x x x x x 1 x
// 7  x x x x x x x 1

int main(int argc, char* argv[]) {
  string s; cin >> s;
  int sz = s.length();
  if (sz & 1) {
    cout << 0 << endl;
    return 0;
  }
  vector<int> dp(sz + 1, 0);
  dp[0] = 1;
  // for (int i = 0; i <= sz; ++i) cout << setw(2) << dp[i]; cout << endl;
  for (int i = 1; i <= sz; ++i) {
    char c = s[i - 1];
    for (int k = i; k >= 0 ; k -= 2) {
      dp[k] = 0;
      if ((c == ')' || c == '?') && k < i)
        dp[k] += dp[k + 1];
      if ((c == '(' || c == '?') && k > 0)
        dp[k] += dp[k - 1];
    }
    // for (int i = 0; i <= sz; ++i) cout << setw(2) << dp[i]; cout << endl;
  }
  cout << dp[0] << endl;
  return 0;
}
