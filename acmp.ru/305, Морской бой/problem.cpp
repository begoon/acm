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

template <typename T>
T max(T a, T b, T c) {
  return max(a, max(b, c));
}

int max_rectangle(vector<string>& f, int* height = 0, int* width = 0) {
  int Y = f.size(), X = f[0].length();
  const char empty = '.';
  int r = 0;
  vector<int> c(Y + 1, 0);
  for (int x = X - 1; x >= 0; --x) {
    for (int y = 0; y < Y; ++y)
      c[y] = f[y][x] == empty ? c[y] + 1 : 0;
    stack<pair<int, int> > s;
    int w = 0;
    for (int y = 0; y <= Y; ++y) {
      if (c[y] > w) {
        s.push(make_pair(y, w));
        w = c[y];
      }
      if (c[y] < w) {
        int y0, w0;
        do {
          assert(!s.empty());
          y0 = s.top().first;
          w0 = s.top().second;
          s.pop();
          if (w * (y - y0) > r) {
            r = w * (y - y0);
            if (width) *width = w;
            if (height) *height = y - y0;
          }
          w = w0;
        } while (c[y] < w);
        w = c[y];
        if (w != 0)
          s.push(make_pair(y0, w0));
      }
    }
  }
  return r;
}

void solve(istream& is, ostream& os) {
  int n, m, k;
  is >> n >> m >> k;
  vector<string> f(n, string(m, '.'));
  while (k--) {
    int x1, y1, x2, y2;
    is >> y1 >> x1 >> y2 >> x2;
    for (int i = y1 - 1; i <= y2 + 1; ++i)
      for (int j = x1 - 1; j <= x2 + 1; ++j)
        if (i >= 1 && i <= n && j >= 1 && j <= m)
          f[i - 1][j - 1] = '*';
  }
  os << max_rectangle(f) << endl;
}

#undef int

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
"8 7 3\n"
"1 1 2 2\n"
"3 5 3 7\n"
"4 2 4 3\n"
,
"21\n"
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

