#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

int cache[81][81];

int f(const string& s, int i, int depth) {
  if (i >= s.length())
    return depth > 0 ? 0 : 1;
  if (cache[i][depth]) return cache[i][depth];
  char c = s[i];
  int r = 0;
  if (c == '(' || c == '?')
    r += f(s, i + 1, depth + 1);
  if (c == ')' || c == '?')
    if (depth > 0) 
      r += f(s, i + 1, depth - 1);
  cache[i][depth] = r;
  return r;
}

int dp[81][81];

//    0 1 2 3 4 5 6 7
// 0  1 x x x x x x x
// 1  x x x x x x x x
// 2  x x x x x x x x
// 3  x x x x x x x x
// 4  x x x x x x x x
// 5  x x x x x x x x
// 6  x x x x x x x x
// 7  x x x x x x x x

int main(int argc, char* argv[]) {
  string s; cin >> s;
  int sz = s.length();
  if (sz == 0 || (sz & 1)) {
    cout << 0 << endl;
    return 0;
  }
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  for (int i = 1; i <= sz; ++i) {
    char c = s[i - 1];
    for (int k = 0; k <= i; ++k) {
      int l = k > 0 ? dp[i - 1][k - 1] : 0;
      int r = k < i ? dp[i - 1][k + 1] : 0;
      if (c == ')' || c == '?')
        dp[i][k] += r;
      if (c == '(' || c == '?')
        dp[i][k] += l;
    }
  }
  cout << dp[sz][0] << endl;
  return 0;
}
