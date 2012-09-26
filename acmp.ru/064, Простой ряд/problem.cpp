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

bool is_prime(int n) {
  if (n == 1) return false;
  else if (n < 4) return true;
  else if (n % 2 == 0) return false;
  else if (n < 9) return true;
  else if (n % 3 == 0) return false;
  else {
    int r = std::sqrt(static_cast<double>(n));
    int f = 5;
    while (f <= r) {
      if (n % f == 0) return false;
      if (n % (f + 2) == 0) return false;
      f += 6;
    }
    return true;
  }
}

void solve(istream& is, ostream& os) {
  string p;
  int i = 2;
  while (p.length() <= 10000) {
    if (is_prime(i)) {
      ostringstream fmt;
      fmt << i;
      p += fmt.str();
    }
    i += 1;
  }
  int n;
  for (is >> n; n > 0; n--) {
    int j;
    is >> j;
    os << p[j - 1];
  }
  os << endl;
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
"3\n"
"1 4 11\n"
,
"271\n"
);

run(__LINE__,
"5\n"
"2 5 6 8 12\n"
,
"31139\n"
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

