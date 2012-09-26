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

int f(vector<vector<int> >& dp, string& s, int n, int k) {
  if (n == 0 && k == 0) return 1;
  if (n == 0) return 0;
  if (k == -1) return 0;
  if (dp[n][k] != -1) return dp[n][k];
  char c = s[n - 1];
  int ans = 0;
  if (c == '?')
    ans = f(dp, s, n - 1, k - 1) + f(dp, s, n - 1, k + 1);
  else if (c == '(')
    ans = f(dp, s, n - 1, k - 1);
  else if (c == ')')
    ans = f(dp, s, n - 1, k + 1);
  dp[n][k] = ans;
  return ans;
}

void solve(istream& is, ostream& os) {
  string s;
  is >> s;
  int n = s.length();
  vector<vector<int> > dp(n + 1, vector<int>(n + 1, -1));
  os << f(dp, s, s.length(), 0) << endl;
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
"????(?\n"
,
"2\n"
);

run(__LINE__,
"???(?\n"
,
"0\n"
);

run(__LINE__,
"?\n"
,
"0\n"
);

run(__LINE__,
"(?\n"
,
"1\n"
);

run(__LINE__,
"()\n"
,
"1\n"
);

run(__LINE__,
")(\n"
,
"0\n"
);

run(__LINE__,
")??(\n"
,
"0\n"
);

run(__LINE__,
"(??)\n"
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

