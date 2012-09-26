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

  int r = 0;
  vector<vector<int> > dp(N, vector<int>(M, 0));
  for (int y2 = 0; y2 < N; ++y2) {
    for (int x2 = 0; x2 < M; ++x2) {
      is >> dp[y2][x2];
      if (y2 > 0)
        dp[y2][x2] += dp[y2-1][x2];
      if (x2 > 0)
        dp[y2][x2] += dp[y2][x2-1];
      if (y2 > 0 && x2 > 0)
        dp[y2][x2] -= dp[y2-1][x2-1];

      for (int y1 = 0; y1 <= y2; ++y1)
        for (int x1 = 0; x1 <= x2; ++x1) {
          int a = dp[y2][x2];
          if (x1 > 0 && y1 > 0)
            a += dp[y1-1][x1-1];
          if (x1 > 0)
            a -= dp[y2][x1-1];
          if (y1 > 0)
            a -= dp[y1-1][x2];
          if (a > r)
            r = a;
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

problem = -1;
problem_filter = -1;

run(__LINE__,
"2 3\n"
"5 0 9\n"
"1 2 7\n"
,
"24\n"
);

run(__LINE__,
"4 5\n" 
"-7 8 -1 0 -2\n"
"2 -9 2 4 -6\n"
"-7 0 6 8 1\n"
"4 -8 -1 0 -6\n"
,
"20\n"
);

ostringstream fmt;
fmt << "100 100" << endl;
for (int i = 0; i < 100 * 100; ++i)
  fmt << 100 << " ";
fmt << endl;

run(__LINE__,
fmt.str().c_str()
,
"1000000\n"
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
