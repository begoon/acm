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

vector<vector<int> > dp;

int f(int i, int j, vector<vector<int> >& m) {
  int r;
  if (i == 0 && j == 0) 
    r = m[i][j];
  else if (i < 0 || j < 0) 
    r = numeric_limits<int>::max();
  else {
    if (dp[i][j] == -1)
      dp[i][j] = m[i][j] + min(f(i-1, j, m), f(i, j-1, m));
    r = dp[i][j];
  }
  return r;
}

void solve_recursive(istream& is, ostream& os) {
  int N, M;
  is >> N >> M;
  vector<vector<int> > m(N, vector<int>(M, 0));
  dp.resize(0);
  dp.resize(N, vector<int>(M, -1));

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      is >> m[i][j];

  os << f(N-1, M-1, m) << endl;
}

void solve(istream& is, ostream& os) {
  int N, M;
  is >> N >> M;
  vector<vector<int> > m(N, vector<int>(M, 0));

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      is >> m[i][j];

  vector<vector<int> > dp(N, vector<int>(M, 0));
  int huge = numeric_limits<int>::max();
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      if (i == 0 && j == 0)
        dp[i][j] = m[i][j];
      else 
        dp[i][j] = m[i][j] + min(i > 0 ? dp[i-1][j] : huge, j > 0 ? dp[i][j-1] : huge);
    }

  os << dp[N-1][M-1] << endl;
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
"3 4\n"
"1 1 1 1\n"
"5 2 2 100\n"
"9 4 2 1\n"
,
"8\n"
);

run(__LINE__,
"5 5\n"
"1 1 1 1 1\n"
"3 100 100 100 100\n"
"1 1 1 1 1\n"
"2 2 2 2 1\n"
"1 1 1 1 1\n"
,
"11\n"
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
