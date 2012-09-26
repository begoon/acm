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

int f(char c, int len, vector<string>& p, vector<int>& m, map<pair<char, int>, int>& dp) {
   if (dp.find(make_pair(c, len)) != dp.end())
    return dp[make_pair(c, len)];

  int r = 1;
  if (len > 1) {
    int t = m[c - 'A'];
    for (int i = 0; i < p[t].length(); ++i)
      r += f(p[t][i], len - 1, p, m, dp);
  }

  dp[make_pair(c, len)] = r;
  return r;
}

void solve(istream& is, ostream& os) {
  vector<string> p(6);
  for (int i = 0; i < p.size(); ++i) getline(is, p[i]);
  char c;
  int len;
  is >> c >> len;
  vector<int> m(26, -1);
  m['N'-'A'] = 0;
  m['S'-'A'] = 1;
  m['W'-'A'] = 2;
  m['E'-'A'] = 3;
  m['U'-'A'] = 4;
  m['D'-'A'] = 5;
  map<pair<char, int>, int> dp;
  int ans = f(c, len, p, m, dp);;
  os << ans << endl;
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
"N\n"
"NUSDDUSE\n"
"UEWWD\n"
"\n"
"U\n"
"WED\n"
"S 3\n"
"\n"
,
"34\n"
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

