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

const double EPS = 1.0E-9;

void solve(istream& is, ostream& os) {
  int N;
  is >> N;

  int m = -1;

  int last;
  int sign;
  int r = 0;
  for (int i = 0; i < N; ++i) {
    int v;
    is >> v;
    if (i == 0) {
      r += 1;
    } else if (i == 1) {
      sign = last < v ? -1 : 1;
      r += 1;
    } else {
      if (sign == -1 && last > v) {
        sign = 1;
        r += 1;
      } else if (sign == 1 && last < v) {
        sign = -1;
        r += 1;
      } else {
        if (r > m)
          m = r;
        r = 2;
        sign = last < v ? -1 : 1;
      }
    }
    last = v;
  }
  if (r > m)
    m = r;
  os << m << endl;
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
"3\n"
"1 2 3\n"
,
"2\n"
);

run(__LINE__,
"12\n"
"5 7 6 3 4 2 7 1 8 9 4 5\n"
,
"7\n"
);

run(__LINE__,
"5\n"
"1 -2 3 -4 5\n"
,
"5\n"
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
