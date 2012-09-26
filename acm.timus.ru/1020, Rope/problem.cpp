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

template <typename T>
T sqr(double x) {
  return x * x;
}

const double PI = 3.14159265;

void solve(istream& is, ostream& os) {
  int n;
  double r;
  is >> n >> r;
  vector<double> x(n), y(n);
  for (int i = 0; i < n; ++i) is >> x[i] >> y[i];
  double d = 0;
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    double l = sqrt(sqr<double>(x[i] - x[j]) + sqr<double>(y[i] - y[j]));
    d += l;
  }
  d += 2 * PI * r;
  os << fixed << setprecision(2) << d << endl;
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
"4 1\n"
"0.0 0.0\n"
"2.0 0.0\n"
"2.0 2.0\n"
"0.0 2.0\n"
,
"14.28\n"
);

#ifdef _DEBUG
getchar();
#endif

#else

// ifstream is("INPUT.TXT");
// ofstream os("OUTPUT.TXT");
istream& is = cin;
ostream& os = cout;

solve(is, os);

#endif

return 0;
}
