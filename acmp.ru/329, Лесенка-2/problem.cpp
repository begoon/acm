#include <iostream>

#include <queue>
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

int max(int a, int b, int c) {
  return max(a, max(b, c));
}

int f(int i, vector<int>& m, vector<int>& p, vector<int>& dp) {
  int r;
  if (dp[i] != -1) return dp[i];
  if (i == 0) {
    p[0] = -1;
    r = m[0];
  } else if (i == 1) {
    if (m[0] > 0) {
      p[1] = 0;
      r = m[0] + m[1];
    } else {
      p[1] = -1;
      r = m[1];
    }
  } else {
    if (f(i-2, m, p, dp) > f(i-1, m, p, dp)) {
      p[i] = i - 2;
      r = f(i-2, m, p, dp) + m[i];
    } else {
      p[i] = i - 1;
      r = f(i-1, m, p, dp) + m[i];
    }
  }
  dp[i] = r;
  return r;
}

void solve_recursive(istream& is, ostream& os) {
  int N;
  is >> N;
  vector<int> m(N);
  for (int i = 0; i < N; ++i) is >> m[i];
  vector<int> p(N);
  vector<int> dp(N, -1);
  os << f(N-1, m, p, dp) << endl;
  deque<int> r;
  int i = N-1;
  while (i != -1) {
    r.push_front(i + 1);
    i = p[i];
  }
  for (int i = 0; i < r.size(); ++i) {
    if (i > 0) os << " ";
    os << r[i];
  }
  os << endl;
}

void solve_pre_read(istream& is, ostream& os) {
  int N;
  is >> N;
  vector<int> m(N);
  for (int i = 0; i < N; ++i) is >> m[i];
  vector<int> p(N);
  vector<int> dp(N, -1);

  for (int i = 0; i < N; ++i) {
    if (i == 0) {
      p[0] = -1;
      dp[0] = m[0];
    } else if (i == 1) {
      if (m[0] > 0) {
        p[1] = 0;
        dp[1] = m[0] + m[1];
      } else {
        p[1] = -1;
        dp[1] = m[1];
      }
    } else {
      int j = dp[i-2] > dp[i-1] ? 2 : 1;
      p[i] = i - j;
      dp[i] = dp[i-j] + m[i];
    }
  }

  os << dp[N-1] << endl;

  deque<int> r;
  int i = N-1;
  while (i != -1) {
    r.push_front(i + 1);
    i = p[i];
  }
  for (int i = 0; i < r.size(); ++i) {
    if (i > 0) os << " ";
    os << r[i];
  }
  os << endl;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;
  vector<int> p(N);
  vector<int> dp(N);

  for (int i = 0; i < N; ++i) {
    int m;
    is >> m;
    if (i == 0) {
      p[0] = -1;
      dp[0] = m;
    } else if (i == 1) {
      if (dp[0] > 0) {
        p[1] = 0;
        dp[1] = dp[0] + m;
      } else {
        p[1] = -1;
        dp[1] = m;
      }
    } else {
      int j = dp[i-2] > dp[i-1] ? 2 : 1;
      p[i] = i - j;
      dp[i] = dp[i-j] + m;
    }
  }

  os << dp[N-1] << endl;

  deque<int> r;
  int i = N-1;
  while (i != -1) {
    r.push_front(i + 1);
    i = p[i];
  }
  for (int i = 0; i < r.size(); ++i) {
    if (i > 0) os << " ";
    os << r[i];
  }
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
"3\n"
"1 2 1\n"
,
"4\n"
"1 2 3\n"
);

run(__LINE__,
"3\n"
"1 -1 1\n"
,
"2\n"
"1 3\n"
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
