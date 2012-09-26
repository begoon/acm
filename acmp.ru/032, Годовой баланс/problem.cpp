#include <iostream>
#include <vector>
#include <map>
#include <set>
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

int f(int v, bool first) {
  stringstream fmt;
  fmt << v;
  string s = fmt.str();
  if (first && v >= 0 || !first && v < 0)
    sort(s.begin() + (v < 0 ? 1 : 0), s.end(), greater<char>());
  else {
    sort(s.begin() + (v < 0 ? 1 : 0), s.end());
    int i = v < 0 ? 1 : 0;
    int j = s.find_first_not_of("0", i);
    if (i != string::npos)
      swap(s[i], s[j]);
  }
  return atoi(s.c_str());
}

void solve(istream& is, ostream& os) {
  int a, b;
  is >> a >> b;
  os << f(a, true) - f(b, false) << endl;
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
"-108\n"
"-10\n"
,
"-98\n"
);

run(__LINE__,
"-18\n"
"-10\n"
,
"-8\n"
);

run(__LINE__,
"18\n"
"10\n"
,
"71\n"
);

run(__LINE__,
"1\n"
"-23\n"
,
"33\n"
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
