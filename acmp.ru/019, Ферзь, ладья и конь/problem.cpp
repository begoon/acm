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
  string a;
  getline(is, a);
  int x1 = a[0] - 'A', y1 = a[1] - '1';
  int x2 = a[3] - 'A', y2 = a[4] - '1';
  int x3 = a[6] - 'A', y3 = a[7] - '1';
  vector<vector<int> > m(8, vector<int>(8, 0));
  m[y1][x1] = 1;
  m[y2][x2] = 1;
  m[y3][x3] = 1;
  struct { int dx, dy; } d1[8] = { {-1, -1}, {+1, -1}, {+1, +1}, {-1, +1}, {-1, 0}, {+1, 0}, {0, -1}, {0, +1} };
  for (int i = 0; i < 8; ++i) {
    int x = x1, y = y1;
    while (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
      if (m[y][x] == 0)
        m[y][x] = 2;
      x += d1[i].dx;
      y += d1[i].dy;
    }
  }
  struct { int dx, dy; } d2[4] = { {-1, 0}, {+1, 0}, {0, -1}, {0, +1} };
  for (int i = 0; i < 4; ++i) {
    int x = x2, y = y2;
    while (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
      if (m[y][x] == 0)
        m[y][x] = 2;
      x += d2[i].dx;
      y += d2[i].dy;
    }
  }
  struct { int dx, dy; } d3[8] = { {-1, -2}, {+1, -2}, {-1, +2}, {+1, +2}, {-2, -1}, {+2, -1}, {-2, +1}, {+2, +1} };
  for (int i = 0; i < 8; ++i) {
    int x = x3 + d3[i].dx, y = y3 + d3[i].dy;
    if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
      if (m[y][x] == 0)
        m[y][x] = 2;
  }
  int r = 0;
  for (int y = 0; y < 8; ++y)
    for (int x = 0; x < 8; ++x)
      if (m[y][x] == 2)
        r += 1;
  os << r << endl;
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
"D1 D3 E5\n"
,
"29\n"
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
