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

int min(int a, int b, int c) {
  return min(a, min(b, c));
}

int f(int r, int c, vector<string>& m, int ch, vector<vector<int> >& dp) {
  if (r < 0 || c < 0 || m[r][c] != ch) return 0;
  if (dp[r][c] != -1) return dp[r][c];
  int v = 1 + min(f(r - 1, c, m, ch, dp), 
                  f(r, c - 1, m, ch, dp), 
                  f(r - 1, c - 1, m, ch, dp));
  dp[r][c] = v;
  return v;
}

void solve(istream& is, ostream& os) {
  int T;
  is >> T;
  for (int t = 1; t <= T; ++t) {
    int M, N, Q;
    is >> M >> N >> Q;
    vector<string> m(M);
    for (int i = 0; i < M; ++i) is >> m[i];
#if 0
    copy(m.begin(), m.end(), ostream_iterator<string>(cout, "\n"));
#endif
    os << M << " " << N << " " << Q << endl;
    for (int q = 0; q < Q; ++q) {
      int r, c;
      is >> r >> c;
      vector<vector<int> > dp(M, vector<int>(N, -1));
      dp[0][0] = 1;
      int sz = f(r, c, m, m[r][c], dp);
#if 0
      cout << r << " " << c << " sz = " << sz << endl;
#endif      
      int ans = 1;
      for (int i = 1; i < sz && r + i < M && c + i < N; ++i) {
        int next = f(r + i, c + i, m, m[r][c], dp);
#if 0
        cout << "i: " << i << ", " << next << endl;
#endif        
        if (next < ans + 2) break;
        ans += 2;
      }
      os << ans << endl;
    }
  }
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
"1\n"
"7 10 5\n"
"abbbaaaaaa\n"
"abbbaaaaaa\n"
"abbbaaaaaa\n"
"aaaaaaaaaa\n"
"aaaaaaaaaa\n"
"aaccaaaaaa\n"
"aaccaaaaaz\n"
"1 2\n"
"2 4\n"
"4 6\n"
"5 2\n"
"6 9\n"
,
"7 10 5\n"
"3\n"
"1\n"
"5\n"
"1\n"
"1\n"
);

#ifdef _DEBUG
getchar();
#endif

#else

// ifstream is("INPUT.TXT");
// ofstream os("OUTPUT.TXT");
istream& is = cin;
ostream& os = cout;

solve(is, os);

#endif

return 0;
}
