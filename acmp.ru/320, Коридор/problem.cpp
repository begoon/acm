#include <iostream>
#include <vector>
#include <map>
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

int N, M;
__int64 c;

void f(int n) {
  if (n == 0)
    c += 1;
  else {
    if (n >= M)
      f(n - M);
    f(n - 1);
  }
}

void solve_bruteforce(istream& is, ostream& os) {
  is >> M >> N;
  c = 0;
  f(N);
  os << c << endl;
}

__int64 g(int n) {
  if (n < 0)
    return 0;
  else if (n == 0)
    return 1;
  else
    return g(n - M) + g(n - 1);
}

void solve_recursive(istream& is, ostream& os) {
  is >> M >> N;
  os << g(N) << endl;
}

__int64 h(int n, vector<__int64>& dp) {
  if (n < 0)
    return 0;
  if (dp[n] != -1) return dp[n];
  __int64 r = 1;
  if (n > 0)
    r = h(n - M, dp) + h(n - 1, dp);
  dp[n] = r;
  return r;
}

void solve_recursive_memo(istream& is, ostream& os) {
  is >> M >> N;
  vector<__int64> dp(N + 1, -1);
  os << h(N, dp) << endl;
}

void solve(istream& is, ostream& os) {
  is >> M >> N;
  vector<__int64> dp(N + 1);
  dp[0] = 1;
  for (int i = 1; i <= N; ++i) {
    dp[i] = dp[i-1];
    if (i >= M)
      dp[i] += dp[i-M];
  }
  os << dp[N] << endl;
}

const char* liner = "--------";
int problem;
int problem_filter;

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
"8 11\n"
,
"5\n"
);

run(__LINE__,
"7 13\n"
,
"8\n"
);

run(__LINE__,
"9 12\n"
,
"5\n"
);

run(__LINE__,
"4 6\n"
,
"4\n"
);

run(__LINE__,
"2 2\n"
,
"2\n"
);

run(__LINE__,
"5 50\n"
,
"644761\n"
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
