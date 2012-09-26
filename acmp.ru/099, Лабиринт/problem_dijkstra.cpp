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

int index(int n, int m, int h, int N, int M, int H) {
  return n + m * N + h * N * M;
}

void solve(istream& is, ostream& os) {
  int H, M, N;
  is >> H >> M >> N;

  vector<vector<string> > f(H);

  for (int h = 0; h < H; ++h) {
    f[h] = vector<string>(M);
    for (int m = 0; m < M; ++m)
      is >> f[h][m] >> ws;
  }

  int nodes = H*M*N;
  vector<vector<int> > g(nodes, vector<int>());

  int dx[] = { +1, -1,  0,  0,  0,  0 };
  int dy[] = {  0,  0, +1, -1,  0,  0 };
  int dz[] = {  0,  0,  0,  0, +1, -1 };

  int start = -1, end = -1;
  for (int h = 0; h < H; ++h)
    for (int m = 0; m < M; ++m)
      for (int n = 0; n < N; ++n) {
        int v = index(n, m, h, N, M, H);
        // cout << v << ": " << h << " " << m << " " << n << endl;
        assert(v < nodes);
        int c = f[h][m][n];
        if (c == 'o') continue;
        else if (c == '1') start = v;
        else if (c == '2') end = v;
        for (int d = 0; d < 6; ++d) {
          int x = n + dx[d], y = m + dy[d], z = h + dz[d];
          if (x < 0 || x >= N || y < 0 || y >= M || z < 0 || z >= H) continue;
          int c = f[z][y][x];
          if (c != 'o') {
            int p = index(x, y, z, N, M, H);
            assert(p < nodes);
            g[v].push_back(p);
          }
        }
      }

  assert(start != -1);
  assert(end != -1);

  vector<bool> visited(nodes, false);
  vector<int> dist(nodes, numeric_limits<int>::max());
  dist[start] = 0;
  while (true) {
    int next_v = numeric_limits<int>::max(), next = -1;
    for (int i = 0; i < dist.size(); ++i) if (!visited[i])
      if (dist[i] < next_v) {
        next_v = dist[i];
        next = i;
      }
    if (next == -1) break;
    visited[next] = true;
    vector<int>& neibours = g[next];
    for (int i = 0; i < neibours.size(); ++i) if (!visited[neibours[i]]) {
      int update = dist[next] + 5;
      if (update < dist[neibours[i]])
        dist[neibours[i]] = update;
    }
  }
  os << dist[end] << endl;
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
