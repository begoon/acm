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

int min3(int a, int b, int c) {
  return min(a, min(b, c));
}

int f(int i, vector<int>& dp, vector<int>& a, vector<int>& b, vector<int>& c) {
  if (i < 0) return 0;
  if (i == 0) return a[0];
  if (dp[i] != -1) return dp[i];
  int r;
  if (i == 1)
    r = min(f(i-1, dp, a, b, c) + a[i], 
            f(i-2, dp, a, b, c) + b[i-1]);
  else
    r = min3(f(i-1, dp, a, b, c) + a[i], 
             f(i-2, dp, a, b, c) + b[i-1], 
             f(i-3, dp, a, b, c) + c[i-2]);
  dp[i] = r;
  return r;
}

void solve_recursive(istream& is, ostream& os) {
  int N;
  is >> N;
  vector<int> a(N), b(N), c(N);
  for (int i = 0; i < N; ++i)
    is >> a[i] >> b[i] >> c[i];
  vector<int> dp(N, -1);
  int r = f(N-1, dp, a, b, c);
  os << r << endl;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;
  vector<int> a(N), b(N), c(N);
  for (int i = 0; i < N; ++i)
    is >> a[i] >> b[i] >> c[i];
  vector<int> dp(N);
  dp[0] = a[0];
  for (int i = 1; i < N; ++i) {
    if (i == 1)
      dp[i] = min(dp[0] + a[1], b[0]);
    else if (i == 2)
      dp[i] = min3(dp[1] + a[2], dp[0] + b[1], c[0]);
    else
      dp[i] = min3(dp[i-1] + a[i], dp[i-2] + b[i-1], dp[i-3] + c[i-2]);
  }
  os << dp[N-1] << endl;
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
"5\n"
"5 10 15\n"
"2 10 15\n"
"5 5 5\n"
"20 20 1\n"
"20 1 1\n"
,
"12\n"
);

run(__LINE__,
"2\n"
"3 4 5\n"
"1 1 1\n"
,
"4\n"
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
