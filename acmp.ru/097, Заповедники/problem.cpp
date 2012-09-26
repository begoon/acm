#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
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

struct point {
  point() : x(0), y(0) {}
  point(int ax, int ay) : x(ax), y(ay) {}
  bool operator==(const point& p) { return x == p.x && y == p.y; }
  int x, y;
};

struct rect {
  rect() {}
  rect(const point& afrom, const point& ato) : from(afrom), to(ato) {
    if (from.x > to.x) swap(from.x, to.x);
    if (from.y > to.y) swap(from.y, to.y);
  }
  point from, to;
};

bool intersect_rect(const point& a1, const point& a2, const point& b1, const point& b2) {
  return min(a2.x, b2.x) > max(a1.x, b1.x) && min(a2.y, b2.y) > max(a1.y, b1.y);
}

bool intersect_rect(const rect& a, const rect& b) {
  return min(a.to.x, b.to.x) > max(a.from.x, b.from.x) && 
         min(a.to.y, b.to.y) > max(a.from.y, b.from.y);
}

void solve(istream& is, ostream& os) {
  int n;
  is >> n;
  vector<rect> a;
  for (int i = 0; i < n; ++i) {
    int x1, y1, r, x2, y2;
    is >> x1 >> y1 >> x2 >> y2 >> r;
    point from(x1, y1), to(x2, y2);
    rect q(from, to);
    q.from.x -= r;
    q.from.y -= r;
    q.to.x += r;
    q.to.y += r;
    a.push_back(q);
  }
  vector<vector<bool> > m(n, vector<bool>(n, false));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (i != j)
        m[i][j] = intersect_rect(a[i], a[j]);
  int ans = -1;
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
"3\n"
"3 1 6 4 1\n"
"1 -2 2 -3 1\n"
"-2 -2 -1 -3 2\n"
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
