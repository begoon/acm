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

#define int long long

struct point {
  int x, y;
};
 
int square(point a, point b, point c) {
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}
 
bool intersect_1(int a, int b, int c, int d) {
  return max(a, b) >= min(c, d) && max(c, d) >= min(a, b);
}
 
bool intersect(point a, point b, point c, point d) {
  int s11 = square(a, b, c);
  int s12 = square(a, b, d);
  int s21 = square(c, d, a);
  int s22 = square(c, d, b);
  if (s11 == 0 && s12 == 0 && s21 == 0 && s22 == 0)
    return intersect_1(a.x, b.x, c.x, d.x) && intersect_1(a.y, b.y, c.y, d.y);
  else
    return s11 * s12 <= 0 && s21 * s22 <= 0;
}

void solve(istream& is, ostream& os) {
  point a, b, c, d;
  is >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
  os << (intersect(a, b, c, d) ? "Yes" : "No") << endl;
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

#ifdef int
#undef int
#endif

int main(int argc, char* argv[]) {
#ifdef TESTING_

problem = -1;
problem_filter = -1;

run(__LINE__,
"-10000 -10000\n"
"10000 10000\n"
"10000 -10000\n"
"0 0\n"
,
"Yes\n"
);

run(__LINE__,
"0 0\n"
"10000 10000\n"
"10000 0\n"
"5001 4999\n"
,
"No\n"
);

run(__LINE__,
"0 0\n"
"10000 10000\n"
"10000 0\n"
"5000 5000\n"
,
"Yes\n"
);

run(__LINE__,
"0 0\n"
"9999 9999\n"
"10000 10000\n"
"10000 10000\n"
,
"No\n"
);

run(__LINE__,
"1 1\n"
"2 2\n"
"3 3\n"
"3 3\n"
,
"No\n"
);

run(__LINE__,
"4 9\n"
"11 2\n"
"1 5\n"
"7 1\n"
,
"No\n"
);

run(__LINE__,
"2 4\n"
"4 2\n"
"1 1\n"
"3 3\n"
,
"Yes\n"
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
