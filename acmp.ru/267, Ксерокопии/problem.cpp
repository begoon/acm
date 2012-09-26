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

void solve_bruteforce(istream& is, ostream& os) {
  long long n, x, y;
  is >> n >> x >> y;
  long long m = numeric_limits<long long>::max();
  n -= 1;
  for (int a = 0; a <= n; ++a) {
    int b = n - a;
    m = min(m, max(a*x, b*y));
  }
  os << m + min(x, y) << endl;
}

void solve(istream& is, ostream& os) {
  long long n, x, y;
  is >> n >> x >> y;
  n -= 1;
  double p = (double)n*y/(x+y);
  long long a1 = floor(p) + EPS;
  long long r1 = max(a1*x, (n-a1)*y);
  long long a2 = ceil(p) + EPS;
  long long r2 = max(a2*x, (n-a2)*y);
  os << min(x, y) + min(r1, r2) << endl;
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
"9 10 1\n"
,
"9\n"
);

run(__LINE__,
"4 1 1\n"
,
"3\n"
);

run(__LINE__,
"5 1 2\n"
,
"4\n"
);

run(__LINE__,
"200000000 1 2\n"
,
"133333334\n"
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
