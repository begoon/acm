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

void solve(istream& is, ostream& os) {
  int n;
  vector<int> g(3600, 0);
  for (is >> n; n > 0; --n) {
    int h1, m1, h2, m2;
    char c;
    is >> h1 >> c >> m1 >> h2 >> c >> m2;
    int t1 = h1 * 60 + m1;
    assert(t1 >= 0 && t1 < 3600);
    int t2 = h2 * 60 + m2;
    assert(t2 >= 0 && t2 < 3600);
    for (int i = t1; i <= t2; ++i)
      g[i] += 1;
  }
  os << *max_element(g.begin(), g.end()) << endl;
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
"6\n"
"09:00 10:07\n"
"10:20 11:35\n"
"12:00 17:00\n"
"11:00 11:30\n"
"11:20 12:30\n"
"11:30 18:15\n"
,
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

