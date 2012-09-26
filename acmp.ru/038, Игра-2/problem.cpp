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

vector<int> v;
vector<vector<int> > dp;
int N;

int f(int i, int j) {
  if (dp[i][j] != -1) 
    return dp[i][j];
  int r;
  if (i == j) 
    r = v[i];
  else if (i + 1 == j) 
    r = max(v[i], v[j]);
  else
    r = max(min(f(i+1, j-1), f(i+2, j)) + v[i], min(f(i, j-2), f(i+1, j-1)) + v[j]);
  dp[i][j] = r;
  return r;
}

void solve_recursive(istream& is, ostream& os) {
  is >> N;
  v.resize(N);
  for (int i = 0; i < N; ++i) is >> v[i];

  dp.resize(0);
  dp.resize(N, vector<int>(N, -1));

  int s = accumulate(v.begin(), v.end(), 0);
  int r = f(0, N-1) * 2;
  os << (r == s ? 0 : (r > s ? 1 : 2)) << endl;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;

  vector<int> v(N);
  for (int i = 0; i < N; ++i) is >> v[i];

  vector<vector<int> > dp(N, vector<int>(N, -1));
  for (int i = 0; i < N; ++i) {
    dp[i][i] = v[i];
    if (i < N-1)
      dp[i][i+1] = max(v[i], v[i+1]);
  }

  for (int i = N - 3; i >= 0; --i)
    for (int j = i + 2; j < N; ++j)
      dp[i][j] = max(min(dp[i+1][j-1], dp[i+2][j]) + v[i], min(dp[i][j-2], dp[i+1][j-1]) + v[j]);

  int s = accumulate(v.begin(), v.end(), 0);
  int r = dp[0][N-1] * 2;
  os << (r == s ? 0 : (r > s ? 1 : 2)) << endl;
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
"0 0 0\n"
,
"0\n"
);

run(__LINE__,
"1\n"
"5\n"
,
"1\n"
);

run(__LINE__,
"4\n"
"3 2 5 4\n"
,
"1\n"
);

run(__LINE__,
"6\n"
"5 5 5 5 5 5\n"
,
"0\n"
);

run(__LINE__,
"9\n"
"2 1 3 2 9 1 2 3 1\n"
,
"2\n"
);

run(__LINE__,
"10\n"
"2 5 3 12 4 6 13 7 1 3\n"
,
"1\n"
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
