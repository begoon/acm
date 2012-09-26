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

template <typename T>
ostream& print(ostream& os, const T& v) {
  copy(v.begin(), v.end(), ostream_iterator<T::value_type>(os, " "));
  return os;
}

bool cmp(const string& s, int i, int sz) {
  for (int j = 0; j < sz; ++j) {
    if (s[j] != s[i - j])
      return false;
  }
  return true;
}

void a_function_bruteforce(const string& s, vector<int>& a) {
  int n = (int)s.length();
  a.resize(n);
  for (int i = 0; i < n; ++i) {
    a[i] = 0;
    for (int sz = 1; sz <= i + 1; ++sz) {
      if (cmp(s, i, sz))
        a[i] = sz;
    }
  }
}

void z_function(const string& s, vector<int>& z) {
  int sz = (int)s.length();
  z.resize(sz);

  int l = 0, r = 0;
  for (int i = 1; i < sz; ++i)
    if (z[i - l] + i <= r)
      z[i] = z[i - l];
    else {
      l = i;
      if (i > r) r = i;
      for (z[i] = r - i; r < sz; ++r, ++z[i])
        if (s[r] != s[z[i]])
          break;
      --r;
    }
}

void a_function(const string& s, vector<int>& a) {
  int sz = (int)s.length();
  string g = s;
  reverse(g.begin(), g.end());
  string t = s + '@' + g;
  vector<int> dp;
  z_function(t, dp);
  a.resize(sz);
  for (int i = 0; i < sz; ++i)
    a[i] = dp[dp.size() - 1 - i];
}

void solve(istream& is, ostream& os) {
  int n;
  string s;
  is >> n >> s;
  assert(n == s.length());
  vector<int> a;
  a_function(s, a);
  for (int i = 0; i < n; ++i) {
    if (i > 0) os << " ";
    os << a[i];
  }
  os << endl;
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
"5\n"
"aabaa\n"
,
"1 2 0 1 5\n"
);

run(__LINE__,
"2\n"
"aa\n"
,
"1 2\n"
);

run(__LINE__,
"5\n"
"acbac\n"
,
"1 0 0 1 0\n"
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

