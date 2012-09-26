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

void solve(istream& is, ostream& os) {
  string s;
  getline(is, s);
  int x1 = s[0] - 'a';
  int y1 = s[1] - '1';
  int x2 = s[4] - 'a';
  int y2 = s[5] - '1';

  struct {
    int x, y;
  } o[] = { 
    {-1, -2}, {+1, -2}, {-2, -1}, {-2, +1},
    {-1, +2}, {+1, +2}, {+2, -1}, {+2, +1},
  };

  for (int i = 0; i < 8; ++i) {
    int fx = x1 + o[i].x;
    int fy = y1 + o[i].y;
    if (fx == x2 && fy == y2) {
      os << 1 << endl;
      return;
    }
    if (fx < 0 || fx > 7 || fy < 0 || fy > 7) continue;
    for (int j = 0; j < 8; ++j) {
      int sx = fx + o[j].x;
      int sy = fy + o[j].y;
      if (sx == x2 && sy == y2) {
        os << 2 << endl;
        return;
      }
    }
  }
  os << "NO" << endl;
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
"a1, h8\n"
,
"NO\n"
);

run(__LINE__,
"a1, b3\n"
,
"1\n"
);

run(__LINE__,
"a1, d4\n"
,
"2\n"
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
