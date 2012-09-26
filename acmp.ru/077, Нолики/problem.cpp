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

int C(int m, int n) {
  int p = 1;
  for (int i = 1; i <= m; i++) {
    p *= n - i + 1;
    p /= i;
  }
  return p;
}

void solve(istream& is, ostream& os) {
  int n, k;
  is >> n >> k;
  int ans = 0;
  int t = n;
  int r = 0;
  while (t) { 
    t >>= 1;
    r += 1;
  }
  for (int i = k + 1; i <= r - 1; ++i) {
    int x = C(k, i - 1);
    ans += x;
  }
  int zeros = 0;
  for (int i = r - 1;  i > 0; --i)
    if ((n >> (i - 1)) & 1)
      ans += C(k - zeros - 1, i - 1);
    else
      zeros += 1;
  if (zeros == k)
    ans += 1;
  os << ans << endl;
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
"8 1\n"
,
"3\n"
);

run(__LINE__,
"13 2\n"
,
"4\n"
);

run(__LINE__,
"1000 5\n"
,
"210\n"
);

run(__LINE__,
"1000000001 5\n"
,
"519185\n"
);

run(__LINE__,
"1000000001 1\n"
,
"419\n"
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

