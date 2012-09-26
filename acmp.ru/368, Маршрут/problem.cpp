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

int f(int i, int j, vector<string>& m, vector<string>& p, vector<vector<int> >& dp) {
  if (i < 0 || j < 0) 
    return numeric_limits<int>::max();
  if (dp[i][j] != -1) return dp[i][j];
  int r = m[i][j] - '0';
  if (i > 0 || j > 0) 
    r += min(f(i-1, j, m, p, dp), f(i, j-1, m, p, dp));
  dp[i][j] = r;
  return r;
}

void solve_recursive(istream& is, ostream& os) {
  int N;
  is >> N >> ws;
  vector<string> m(N);

  for (int i = 0; i < N; ++i)
    getline(is, m[i]);

  vector<string> p(N);
  for (int i = 0; i < N; ++i)
    p[i] = string(N, '.');

  vector<vector<int> > dp(N, vector<int>(N, -1));

  int i = N-1, j = N-1;
  do {
    p[i][j] = '#';
    if (i == 0 && j == 0) break;
    if (i == 0)
      j -= 1;
    else if (j == 0)
      i -= 1;
    else {
      if (f(i-1, j, m, p, dp) < f(i, j-1, m, p, dp))
        i -= 1;
      else
        j -= 1;
    }
  } while (true);
  copy(p.begin(), p.end(), ostream_iterator<string>(os, "\n"));
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N >> ws;
  vector<string> m(N);

  for (int i = 0; i < N; ++i)
    getline(is, m[i]);

  vector<string> p(N);
  for (int i = 0; i < N; ++i)
    p[i] = string(N, '.');

  vector<vector<int> > dp(N, vector<int>(N, -1));

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
      dp[i][j] = m[i][j] - '0';
      if (i == 0 && j == 0) continue;
      if (i == 0)
        dp[i][j] += dp[i][j-1];
      else if (j == 0)
        dp[i][j] += dp[i-1][j];
      else
        dp[i][j] += min(dp[i-1][j], dp[i][j-1]);
    }

  int i = N-1, j = N-1;
  do {
    p[i][j] = '#';
    if (i == 0 && j == 0) break;
    if (i == 0)
      j -= 1;
    else if (j == 0)
      i -= 1;
    else {
      if (dp[i-1][j] < dp[i][j-1])
        i -= 1;
      else
        j -= 1;
    }
  } while (true);
  copy(p.begin(), p.end(), ostream_iterator<string>(os, "\n"));
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
"943\n"
"216\n"
"091\n"
,
"#..\n"
"###\n"
"..#\n"
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
