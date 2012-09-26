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

struct xy { int x, y; };

bool available(int x, int y, vector<xy>& m) {
  for (int i = 0; i < m.size(); ++i) {
    if (m[i].x == x || m[i].y == y)
      return false;
    if (m[i].y - m[i].x == y - x)
      return false;
    if (m[i].y + m[i].x == y + x)
      return false;
  }

  for (int i = 0; i < m.size(); ++i) {
    if (m[i].x + 1 == x && m[i].y - 2 == y)
      return false;
    if (m[i].x + 1 == x && m[i].y + 2 == y)
      return false;
    if (m[i].x + 2 == x && m[i].y - 1 == y)
      return false;
    if (m[i].x + 2 == x && m[i].y + 1 == y)
      return false;
    /*
    if (m[i].x - 1 == x && m[i].y - 2 == y)
      return false;
    if (m[i].x - 1 == x && m[i].y + 2 == y)
      return false;
    if (m[i].x - 2 == x && m[i].y - 1 == y)
      return false;
    if (m[i].x - 2 == x && m[i].y + 1 == y)
      return false;
    */
  }

  return true;
}

void f(int sx, vector<xy>& m, int& r, int N, int K) {
  if (m.size() == K) {
    r += 1;
    return;
  }

  for (int x = sx; x < N; ++x)
    for (int y = 0; y < N; ++y)
      if (available(x, y, m)) {
        xy p;
        p.x = x;
        p.y = y;
        m.push_back(p);
        f(x + 1, m, r, N, K);
        m.pop_back();
      }
}

void solve(istream& is, ostream& os) {
  int N,  K;
  is >> N >> K;

  int r = 0;
  vector<xy> m;
  f(0, m, r, N, K);
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
"3 1\n"
,
"9\n"
);

run(__LINE__,
"4 2\n"
,
"20\n"
);

run(__LINE__,
"5 2\n"
,
"92\n"
);

run(__LINE__,
"5 3\n"
,
"48\n"
);

run(__LINE__,
"10 5\n"
,
"562384\n"
);

run(__LINE__,
"10 8\n"
,
"562384\n"
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
