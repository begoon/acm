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
  int N, M, X, Y;
  is >> N >> M >> Y >> X;
  vector<vector<int> > m(N, vector<int>(M, 1));

  struct {
    int y, x;
  } d[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
  
  int r = 0;
  int x = 0, y = 0;

  int t = 0;
  while (true) {
    r += 1;
    m[y][x] = 0;
    if (x == X-1 && y == Y-1) break;
    if (x + d[t].x < 0 || x + d[t].x >= M || y + d[t].y < 0 || y + d[t].y >= N || 
        m[y + d[t].y][x + d[t].x] == 0)
      t = (t + 1) % 4;
    x += d[t].x;
    y += d[t].y;
  }

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

problem = 0;
problem_filter = -1;

run(__LINE__,
"1 1\n"
"1 1\n"
,
"1\n"
);

run(__LINE__,
"3 3\n"
"2 3\n"
,
"4\n"
);

run(__LINE__,
"5 5\n"
"2 3\n"
,
"18\n"
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
