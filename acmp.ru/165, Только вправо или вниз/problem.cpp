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

void solve(istream& is, ostream& os) {
  int N, M;
  is >> N >> M;
  vector<vector<int> > m(N, vector<int>(M, 0));

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      is >> m[i][j];

  vector<vector<int> > dp(N, vector<int>(M, 0));
  dp[0][0] = 1;

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      if (i == N-1 && j == M-1) continue;
      int v = m[i][j];
      if (i + v < N)
        dp[i + v][j] += dp[i][j];
      if (j + v < M)
        dp[i][j + v] += dp[i][j];
    }

  os << dp[N-1][M-1] << endl;
}

int f(int i, int j, vector<vector<int> >& m, vector<vector<int> >& dp) {
  if (dp[i][j] != -1) 
    return dp[i][j];
  int r;
  if (i == 0 && j == 0) 
    r = 1;
  else {
    r = 0;
    for (int x = 0; x < j; ++x)
      if (x + m[i][x] == j)
        r += f(i, x, m, dp);
    for (int y = 0; y < i; ++y)
      if (y + m[y][j] == i)
        r += f(y, j, m, dp);
  }
  dp[i][j] = r;
  return r;
}

void solve_recursive(istream& is, ostream& os) {
  int N, M;
  is >> N >> M;
  vector<vector<int> > m(N, vector<int>(M, 0));

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      is >> m[i][j];

  vector<vector<int> > dp(N, vector<int>(M, -1));
  os << f(N-1, M-1, m, dp) << endl;
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
"3 4\n"
"2 1 1 2\n"
"3 2 1 44\n"
"3 1 1 0\n"
,
"3\n"
);

run(__LINE__,
"6 6\n" 
"2 0 5 0 0 0\n"
"1 0 0 0 0 0\n"
"1 0 0 0 0 0\n"
"1 0 0 0 0 0\n"
"1 0 0 0 0 0\n"
"1 1 3 0 0 0\n"
,
"2\n"
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
