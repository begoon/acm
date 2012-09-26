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

double a_(int x1, int y1, int x2, int y2, int x3, int y3) {
  return fabs((double)(x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2.0;
}

int a(int x1, int y1, int x2, int y2, int x3, int y3) {
  return abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));
}

void solve(istream& is, ostream& os) {
  int x1, y1, x2, y2, x3, y3, x, y;
  is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x >> y;

  int s = a(x1, y1, x2, y2, x3, y3);
  int s1 = a(x1, y1, x2, y2, x, y);
  int s2 = a(x1, y1, x, y, x3, y3);
  int s3 = a(x, y, x2, y2, x3, y3);
  os << (s == s1 + s2 + s3 ? "In" : "Out") << endl;
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
"0 0\n"
"100 0\n"
"0 100\n"
"100 100\n"
,
"Out\n"
);

run(__LINE__,
"0 0\n"
"100 0\n"
"0 100\n"
"10 10\n"
,
"In\n"
);

run(__LINE__,
"0 0\n"
"100 0\n"
"0 100\n"
"50 50\n"
,
"In\n"
);

run(__LINE__,
"0 0\n"
"100 0\n"
"0 100\n"
"0 0\n"
,
"In\n"
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
