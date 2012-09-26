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

template <typename T>
T max(T a, T b, T c) {
  return max(a, max(b, c));
}

void solve(istream& is, ostream& os) {
  int n;
  is >> n;
  int h = n*2 - 1;
  vector<vector<bool> > m(h, vector<bool>(h, false));
  for (int y = 0; y < n; ++y)
    for (int x = 0; x < n + y; ++x)
      m[y][x] = m[h - y - 1][h - x - 1] = true;
  vector<vector<long long> > dp(h, vector<long long>(h, 0));
  dp[0][0] = 1;
  for (int y = 0; y < h; ++y)
    for (int x = 0; x < h; ++x) 
      if (m[y][x]) {
        if (x > 0 && m[y][x-1])
          dp[y][x] += dp[y][x-1];
        if (y > 0 && m[y-1][x])
          dp[y][x] += dp[y-1][x];
        if (x > 0 && y > 0 && m[y-1][x-1])
          dp[y][x] += dp[y-1][x-1];
      }
  os << dp[h-1][h-1] << endl;
}

#undef int

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
"2\n"
,
"11\n"
);

run(__LINE__,
"3\n"
,
"291\n"
);

run(__LINE__,
"12\n"
,
"8441983967058723\n"
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

