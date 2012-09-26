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

void solve(istream& is, ostream& os) {
  int H, W, N;
  is >> H >> W >> N;
  vector<vector<int> > dp(H, vector<int>(W, 0));
  for (int h = 0; h < H; ++h) {
    for (int w = 0; w < W; ++w) {
      is >> dp[h][w];
      if (h > 0) dp[h][w] += dp[h - 1][w];
      if (w > 0) dp[h][w] += dp[h][w - 1];
      if (h > 0 && w > 0) dp[h][w] -= dp[h - 1][w - 1];
    }
  }
  is >> ws;
  for (int n = 0; n < N; ++n) {
    int y1, x1, y2, x2;
    is >> y1 >> x1 >> y2 >> x2;
    string line;
    getline(is, line);
    sscanf(line.c_str(), "%d %d %d %d", &y1, &x1, &y2, &x2);
    if (y1 > y2) swap(y1, y2);
    if (x1 > x2) swap(x1, x2);
    --y1; --x1; --y2; --x2;
    int v = dp[y2][x2];
    if (x1 > 0)
      v -= dp[y2][x1 - 1];
    if (y1 > 0)
      v -= dp[y1 - 1][x2];
    if (x1 > 0 && y1 > 0)
      v += dp[y1 - 1][x1 - 1];
    os << v << endl;
  }
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
"2 3 1\n"
"5 1 2\n"
"6 7 3\n"
"2 1 2 3\n"
,
"16\n"
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

