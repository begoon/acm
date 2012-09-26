#include <iostream>
#include <vector>
#include <map>
#include <deque>
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

const double EPS = 1.0E-9;

void solve_long(istream& is, ostream& os) {
  int N;
  is >> N;

  if (N == 0) {
    os << 10 << endl;
    return;
  }

  vector<int> f;
  for (int i = 2; i*i <= N; ++i) {
    while (N % i == 0) {
      f.push_back(i);
      N /= i;
    }
  }
  if (N > 1)
    f.push_back(N);
  vector<int> r;
  for (int i = f.size() - 1; i >= 0; --i) {
    if (f[i] > 9) {
      os << -1 << endl;
      return;
    }
    if (i == 0)
      r.push_back(f[i]);
    else {
      int m = f[i];
      while (i > 0 && m * f[i-1] <= 9) {
        m *= f[i-1];
        --i;
      }
      r.push_back(m);
    }
  }
  sort(r.begin(), r.end());
  copy(r.begin(), r.end(), ostream_iterator<int>(os));
  os << endl;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;

  if (N == 0) {
    os << 10 << endl;
    return;
  }

  deque<int> f;
  for (int i = 9; i >= 2; --i) {
    while (N % i == 0) {
      f.push_front(i);
      N /= i;
    }
  }
  if (N > 9) {
    os << -1 << endl;
    return;
  }
  if (N > 1)
    f.push_front(N);
  copy(f.begin(), f.end(), ostream_iterator<int>(os));
  os << endl;
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
"0\n"
,
"10\n"
);

run(__LINE__,
"8192\n"
,
"28888\n"
);

run(__LINE__,
"9765625\n"
,
"5555555555\n"
);

run(__LINE__,
"976562500\n"
,
"4555555555555\n"
);

run(__LINE__,
"2048\n"
,
"4888\n"
);

run(__LINE__,
"90\n"
,
"259\n"
);

run(__LINE__,
"10\n"
,
"25\n"
);

run(__LINE__,
"13\n"
,
"-1\n"
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
