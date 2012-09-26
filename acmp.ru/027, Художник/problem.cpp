#include <iostream>
#include <vector>
#include <map>
#include <set>
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

int sqr(int x) {
  return x * x;
}

void solve(istream& is, ostream& os) {
  int w, h, n;
  is >> w >> h >> n;
  vector<vector<bool> > m(w, vector<bool>(h, true));
  int cnt = w * h;
  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2;
    is >> x1 >> y1 >> x2 >> y2;
    for (int x = x1; x < x2; ++x)
      for (int y = y1; y < y2; ++y) {
        if (m[x][y])
          cnt -= 1;
        m[x][y] = false;
      }
  }
  os << cnt << endl;
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
"5 5\n"
"2\n"
"1 1 3 3\n"
"2 2 4 4\n"
,
"18\n"
);

run(__LINE__,
"6 7\n"
"3\n"
"0 0 5 5\n"
"1 1 4 4\n"
"2 2 3 3\n"
,
"17\n"
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
