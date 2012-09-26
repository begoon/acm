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
  double R = 100, U = 0, E = 0;
  while (n--) {
    double one_U, one_E;
    is >> one_U >> one_E;
    double r = max(R, U * one_U, E * one_E);
    double u = max(R / one_U, U, E * one_E / one_U);
    double e = max(R / one_E, U * one_U / one_E, E);
    R = r;
    U = u;
    E = e;
  }
  os << fixed << setprecision(2) << R << endl;
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
"4\n"
"1 10\n"
"10 5.53\n"
"5.53 1.25\n"
"6 5\n"
,
"4000.00\n"
);

run(__LINE__,
"2\n"
"1 10\n"
"10 5.53\n"
,
"1000.00\n"
);

run(__LINE__,
"3\n"
"1 10\n"
"10 5.53\n"
"5.53 1.25\n"
,
"1000.00\n"
);

run(__LINE__,
"1\n"
"0 0\n"
,
"100.00\n"
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

