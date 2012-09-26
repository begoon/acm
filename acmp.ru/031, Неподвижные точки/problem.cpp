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

void f(int pos, int N, int K, vector<bool>& u, int c, int& r) {
  if (pos >= N) {
    if (c == K)
      r += 1;
    return;
  }
  for (int i = 0; i < N; ++i) if (!u[i]) {
    u[i] = true;
    int p = pos == i ? 1 : 0;
    if (c + p <= K)
      f(pos + 1, N, K, u, c + p, r);
    u[i] = false;
  }
}

void solve_recursive(istream& is, ostream& os) {
  int N,  K;
  is >> N >> K;

  vector<bool> u(N, false);
  int r = 0;
  f(0, N, K, u, 0, r);
  os << r << endl;
}

void solve(istream& is, ostream& os) {
  int N,  K;
  is >> N >> K;

  vector<int> v(N);
  for (int i = 0; i < N; ++i) v[i] = i;
  int r = 0;
  do {
    int c = 0;
    for (int i = 0; i < N; ++i)
      if (v[i] == i)
        c += 1;
    if (c == K)
      r += 1;
  } while (next_permutation(v.begin(), v.end()));
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
"5 2\n"
,
"20\n"
);

run(__LINE__,
"9 6\n"
,
"168\n"
);

run(__LINE__,
"2 1\n"
,
"0\n"
);

run(__LINE__,
"9 0\n"
,
"133496\n"
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
