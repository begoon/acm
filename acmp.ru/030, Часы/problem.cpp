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

void solve(istream& is, ostream& os) {
  int h1, m1, s1, h2, m2, s2;
  char c;
  is >> h1 >> c >> m1 >> c >> s1 >> h2 >> c >> m2 >> c >> s2;
  vector<int> u(10, 0);
  int from = s1 + m1 * 60 + h1 * 3600;
  int to = s2 + m2 * 60 + h2 * 3600;
  for (int i = from; i <= to; ++i) {
    int h = i / 3600;
    int s = i % 60;
    int m = (i / 60) % 60;
    char f[8 + 1];
    sprintf(f, "%02d:%02d:%02d", h, m, s);
    for (int i = 0; i < 8; ++i)
      if (isdigit(f[i]))
        u[f[i] - '0'] += 1;
  }
  for (int i = 0; i < u.size(); ++i)
    os << u[i] << endl;
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
"00:00:00\n"
"00:00:00\n"
,
"6\n"
"0\n"
"0\n"
"0\n"
"0\n"
"0\n"
"0\n"
"0\n"
"0\n"
"0\n"
);

run(__LINE__,
"00:00:00\n"
"23:59:59\n"
,
"92880\n"
"92880\n"
"71280\n"
"56880\n"
"53280\n"
"53280\n"
"24480\n"
"24480\n"
"24480\n"
"24480\n"
);

run(__LINE__,
"23:59:59\n"
"23:59:59\n"
,
"0\n"
"0\n"
"1\n"
"1\n"
"0\n"
"2\n"
"0\n"
"0\n"
"0\n"
"2\n"
);

run(__LINE__,
"23:59:58\n"
"23:59:59\n"
,
"0\n"
"0\n"
"2\n"
"2\n"
"0\n"
"4\n"
"0\n"
"0\n"
"1\n"
"3\n"
);

run(__LINE__,
"13:24:09\n"
"13:24:40\n"
,
"5\n"
"45\n"
"45\n"
"45\n"
"36\n"
"3\n"
"3\n"
"3\n"
"3\n"
"4\n"
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
