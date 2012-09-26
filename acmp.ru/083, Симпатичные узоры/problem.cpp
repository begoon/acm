#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <limits>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

const double EPS = 1e-9;

void f(vector<vector<int> >& dp, int m, int n, int prev_mask, int mask, int N) {
  if (n == N) {
    dp[m][mask] += dp[m - 1][prev_mask];
    return;
  }
  int left = mask & (1 << (n - 1));
  int above = prev_mask & (1 << n);
  int diag = prev_mask & (1 << (n - 1));
  if (n == 0 || left || above || diag)
    f(dp, m, n + 1, prev_mask, mask, N);
  if (n == 0 || !left || !above || !diag)
    f(dp, m, n + 1, prev_mask, mask | (1 << n), N);
}

void solve(istream& is, ostream& os) {
  int M, N;
  is >> M >> N;
  vector<vector<int> > dp(M, vector<int>(1 << N, 0));
  for (int i = 0; i < dp[0].size(); ++i) dp[0][i] = 1;
  for (int m = 1; m < M; ++m) {
    for (int mask = 0; mask < (1 << N); ++mask) {
      if (dp[m - 1][mask] > 0)
        f(dp, m, 0, mask, 0, N);
    }
  }
  int ans = accumulate(dp[M-1].begin(), dp[M-1].end(), 0);
  os << ans << endl;
}

const char* liner = "--------";
int problem;
int problem_filter;

#ifdef int
#undef int
#endif

void run(int line, const char* input, const char* output) {
  problem += 1;
  if (problem_filter != -1 && problem_filter != problem) return;

  stringstream is(input);
  stringstream os;
  solve(is, os);
  if (os.str() != output) {
    cerr << "Case #" << problem << ": FAILED (line " << line << ")" << endl;
#ifdef _DEBUG
    stringstream error;
    error << __FILE__ << "(" << line << "): error: test case " << problem << " FAILED" << endl;
    OutputDebugStringA(error.str().c_str());  
#endif
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else 
    cerr << "Case #" << problem << " OK (line " << line << ")" << endl;
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

problem = -1;
problem_filter = -1;

run(__LINE__,
"1 1\n"
,
"2\n"
);

run(__LINE__,
"2 2\n"
,
"14\n"
);

run(__LINE__,
"2 3\n"
,
"50\n"
);

run(__LINE__,
"3 3\n"
,
"322\n"
);

#ifdef _DEBUG
getchar();
#endif

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
// istream& is = cin;
// ostream& os = cout;

solve(is, os);

#endif

return 0;
}

