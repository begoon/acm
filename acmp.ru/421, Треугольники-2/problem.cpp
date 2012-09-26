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

int a(int x1, int y1, int x2, int y2, int x3, int y3) {
  return (x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
}

int l(int x1, int y1, int x2, int y2) {
  return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;

  int x1, y1, x2, y2, x3, y3;
  is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  int s = a(x1, y1, x2, y2, x3, y3);
  if (s < 0) {
    swap(x2, x3);
    swap(y2, y3);
    s = a(x1, y1, x2, y2, x3, y3);
    assert(s >= 0);
  }
  int l1 = l(x1, y1, x2, y2);
  int l2 = l(x2, y2, x3, y3);
  int l3 = l(x3, y3, x1, y1);

  while (--N) {
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    int s = a(x1, y1, x2, y2, x3, y3);
    if (s < 0) {
      swap(x2, x3);
      swap(y2, y3);
      s = a(x1, y1, x2, y2, x3, y3);
      assert(s >= 0);
    }
    int c1 = l(x1, y1, x2, y2);
    int c2 = l(x2, y2, x3, y3);
    int c3 = l(x3, y3, x1, y1);
    if ((l1 != c1 || l2 != c2 || l3 != c3) &&
        (l1 != c2 || l2 != c3 || l3 != c1) &&
        (l1 != c3 || l2 != c1 || l3 != c2)) {
      os << "NO" << endl;
      return;
    }
  }
  os << "YES" << endl;
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
"1 1 1 2 2 1\n"
"2 1 2 2 1 2\n"
"1 1 2 1 2 2\n"
,
"YES\n"
);

run(__LINE__,
"2\n"
"1 1 4 1 2 2\n"
"1 1 4 1 3 2\n"
,
"NO\n"
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
