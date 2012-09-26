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

int index(int n, int m, int h, int N, int M, int H) {
  return n + m * N + h * N * M;
}

#define cell(n, m, h) f[(n) + (m) * N + (h) * N * M]

struct point {
  point() : x(0), y(0), z(0), dist(0) {}
  point(int ax, int ay, int az, int adist) : x(ax), y(ay), z(az), dist(adist) {}
  bool operator==(const point& p) { return x == p.x && y == p.y && z == p.z; }
  int x, y, z, dist;
};

void solve(istream& is, ostream& os) {
  int H, M, N;
  is >> H >> M >> N;
  int nodes = H * M * N;
  vector<bool> f(nodes, false);

  point start, end;
  for (int h = 0; h < H; ++h)
    for (int m = 0; m < M; ++m)
      for (int n = 0; n < N; ++n) {
        char c;
        is >> c;
        if (c == '.' || c == 'o' || c == '1' || c == '2') {
          if (c == '1') start = point(n, m, h, 0);
          if (c == '2') end = point(n, m, h, 0);
          cell(n, m, h) = c != 'o';
        }
      }

  int dx[] = { +1, -1,  0,  0,  0,  0 };
  int dy[] = {  0,  0, +1, -1,  0,  0 };
  int dz[] = {  0,  0,  0,  0, +1,  0 };

  queue<point> q;
  q.push(start);

  int ans = -1;
  while (!q.empty() && ans == -1) {
    point p = q.front();
    q.pop();
    for (int d = 0; d < 6; ++d) {
      point a(p.x + dx[d], p.y + dy[d], p.z + dz[d], p.dist + 1);
      if (a.x < 0 || a.x >= N || a.y < 0 || a.y >= M || a.z < 0 || a.z >= H) continue;
      if (a == end) {
        ans = a.dist * 5;
        break;
      }

      bool c = cell(a.x, a.y, a.z);
      if (!c) continue;
      cell(a.x, a.y, a.z) = false;
      q.push(a);
    }
  }
  assert(ans != -1);
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
"1 1 2\n"
"12\n"
,
"5\n"
);

run(__LINE__,
"3 3 3\n"
"1..\n"
"oo.\n"
"...\n"
"\n"
"ooo\n"
"..o\n"
".oo\n"
"\n"
"ooo\n"
"o..\n"
"o.2\n"
,
"60\n"
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
