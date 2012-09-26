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

struct state {
  int e, f;
  int n;
  vector<int> g;
  vector<int> w;
  vector<int> p;
};

int m(int t, state& s) {
  if (t < 1) return 0;
  if (s.g[t] != -1) return s.g[t];
  int r = -1;
  for (int i = 0; i < s.n; ++i) {
    r = max(r, m(t - s.w[i], s) + s.p[i]);
  }
  assert(r != -1);
  s.g[t] = max(m(t - 1, s), r);
  return s.g[t];
}

void solve_recursive(istream& is, ostream& os) {
  state s;
  is >> s.e >> s.f >> s.n;
  s.w.resize(s.n);
  s.p.resize(s.n);
  s.g.resize(s.f - s.e + 1, -1);
  for (int i = 0; i < s.n; ++i) is >> s.p[i] >> s.w[i];
  os << m(s.f - s.e, s) << endl;
}

void solve(istream& is, ostream& os) {
  int e, f, n;
  is >> e >> f >> n;
  int g = f - e;
  vector<int> w(n), p(n);
  for (int i = 0; i < n; ++i) is >> p[i] >> w[i];
  vector<int> dp(g + 1, -1);
  dp[0] = 0;
  for (int i = 1; i <= g; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i - w[j] < 0 || dp[i - w[j]] == -1) continue;
      int v = dp[i - w[j]] + p[j];
      dp[i] = dp[i] == -1 ? v : min(dp[i], v);
    }
  }
  if (dp[g] == -1) {
    os << "This is impossible." << endl; 
    return;
  }
  os << dp[g] << " ";
  fill_n(dp.begin(), g + 1, -1);
  dp[0] = 0;
  for (int i = 1; i <= g; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i - w[j] < 0 || dp[i - w[j]] == -1) continue;
      int v = dp[i - w[j]] + p[j];
      dp[i] = dp[i] == -1 ? v : max(dp[i], v);
    }
  }
  if (dp[g] == -1) {
    os << "This is impossible." << endl; 
    return;
  }
  os << dp[g] << endl;
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
"1000 1100\n"
"2\n"
"1 1\n"
"5 2\n"
,
"100 250\n"
);

run(__LINE__,
"1000 1010\n"
"2\n"
"6 3\n"
"2 2\n"
,
"10 16\n"
);

run(__LINE__,
"1000 2000\n"
"1\n"
"10 3\n"
,
"This is impossible.\n"
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

