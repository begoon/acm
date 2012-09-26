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

void solve(istream& is, ostream& os) {
  string s;
  is >> s;
  int n = s.length();
  vector<vector<int> > m(n, vector<int>(n, -1));
  for (int d = 0; d < n; ++d) {
    for (int l = 0; l < n - d; ++l) {
      int r = d + l;
      if (l == r)
        m[l][r] = 2;
      else if (s[l] == ')' || s[l] == ']' || s[l] == '}') {
        assert(m[l+1][r] != -1);
        m[l][r] = 2 + m[l+1][r];
      } else if (s[r] == '(' || s[r] == '[' || s[r] == '{') {
        assert(m[l][r-1] != -1);
        m[l][r] = 2 + m[l][r-1];
      } else if ((s[l] == '(' && (s[r] == ']' || s[r] == '}')) ||
                 (s[l] == '[' && (s[r] == ')' || s[r] == '}')) ||
                 (s[l] == '{' && (s[r] == ')' || s[r] == ']'))) {
        int o = numeric_limits<int>::max();
        for (int e = l; e < r; ++e) {
          assert(m[l][e] != -1);
          assert(m[e+1][r] != -1);
          int t = m[l][e] + m[e+1][r];
          if (t < o)
            o = t;
        }
        m[l][r] = o;
      } else if ((s[l] == '(' && s[r] == ')') ||
                 (s[l] == '[' && s[r] == ']') ||
                 (s[l] == '{' && s[r] == '}')) {
        int o = numeric_limits<int>::max();
        for (int e = l; e < r; ++e) {
          assert(m[l][e] != -1);
          assert(m[e+1][r] != -1);
          int t = m[l][e] + m[e+1][r];
          if (t < o)
            o = t;
        }
        if (r > l + 1) {
          assert(m[l+1][r-1] != -1);
          if (1 + m[l+1][r-1] + 1 < o)
            o = min(o, 1 + m[l+1][r-1] + 1);
        } else
          o = min(2, o);
        m[l][r] = o;
      }
    }
  }
  os << m[0][n-1] - n << endl;
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
"{}\n"
,
"0\n"
);

run(__LINE__,
"())\n"
,
"1\n"
);

run(__LINE__,
"([{}])\n"
,
"0\n"
);

run(__LINE__,
"(\n"
,
"1\n"
);

run(__LINE__,
"}\n"
,
"1\n"
);

run(__LINE__,
"{(})\n"
,
"2\n"
);

run(__LINE__,
"(])][)}){{{{)([)]]\n"
,
"12\n"
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
