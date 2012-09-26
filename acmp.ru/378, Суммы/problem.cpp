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

void solve_full(istream& is, ostream& os) {
  int N;
  is >> N;

  vector<int> v(N);
  for (int i = 0; i < N; ++i) is >> v[i];
  int S = accumulate(v.begin(), v.end(), 0);

  vector<vector<bool> > dp(N + 1, vector<bool>(S + 1, false));
  for (int i = 0; i <= N; ++i)
    dp[i][0] = true;

  int r = 0;
  for (int i = 1; i <= N; ++i)
    for (int j = 0; j <= S; ++j) {
      dp[i][j] = dp[i-1][j] || (j >= v[i-1] && dp[i-1][j-v[i-1]]);
      if (dp[i][j] && i == N)
        r += 1;
    }

  os << r << endl;
}

void solve_2_lines_array(istream& is, ostream& os) {
  int N;
  is >> N;

  vector<int> v(N);
  for (int i = 0; i < N; ++i) is >> v[i];
  int S = accumulate(v.begin(), v.end(), 0);

  vector<vector<bool> > dp(2, vector<bool>(S + 1, false));
  dp[0][0] = true;

  int r = 0;
  for (int i = 1; i <= N; ++i)
    for (int j = 0; j <= S; ++j) {
      dp[i & 1][j] = dp[(i-1) & 1][j] || (j >= v[i-1] && dp[(i-1) & 1][j-v[i-1]]);
      if (dp[i & 1][j] && i == N)
        r += 1;
    }

  os << r << endl;
}

void solve_1_line_array(istream& is, ostream& os) {
  int N;
  is >> N;

  vector<int> v(N);
  for (int i = 0; i < N; ++i) is >> v[i];
  int S = accumulate(v.begin(), v.end(), 0);

  vector<bool> dp(S + 1, false);
  dp[0] = true;

  for (int i = 1; i <= N; ++i)
    for (int j = S; j >= v[i-1]; --j)
      dp[j] = dp[j] || (j >= v[i-1] && dp[j-v[i-1]]);

  int r = 0;
  for (int i = 0; i <= S; ++i)
    if (dp[i])
      r += 1;
  os << r << endl;
}

void solve_no_boundary_check(istream& is, ostream& os) {
  int N;
  is >> N;

  vector<int> v(N);
  for (int i = 0; i < N; ++i) is >> v[i];
  int S = accumulate(v.begin(), v.end(), 0);

  vector<bool> dp(S + 1, false);
  dp[0] = true;

  for (int i = 1; i <= N; ++i)
    for (int j = S; j >= v[i-1]; --j)
      dp[j] = dp[j] || dp[j-v[i-1]];

  int r = accumulate(dp.begin(), dp.end(), 0);
  os << r << endl;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;

  const int S = 50001;
  vector<bool> dp(S + 1, false);
  int r = 1;
  dp[0] = true;

  for (int i = 1; i <= N; ++i) {
    int v;
    is >> v;
    for (int j = S; j >= v; --j) {
      if (dp[j-v]) {
        if (!dp[j]) 
          r += 1;
        dp[j] = true;
      }
    }
  }

  os << r << endl;
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

problem = 0;
problem_filter = -1;

run(__LINE__,
"3\n"
"1 1 2\n"
,
"5\n"
);

run(__LINE__,
"3\n"
"1 3 2\n"
,
"7\n"
);

run(__LINE__,
"5\n"
"49 100 98 49 0\n"
,
"10\n"
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
