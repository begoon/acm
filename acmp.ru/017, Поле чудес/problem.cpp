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

const double EPS = 1.0E-9;

vector<int> prefix_function(const vector<int>& s) {
  int n = (int)s.size();
  vector<int> pi(n);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;
  vector<int> v(N);
  for (int i = 0; i < N; ++i) is >> v[i];
  vector<int> p = prefix_function(v);
  int r = N - p[N-1];
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
"5\n"
"1 2 1 1 1\n"
,
"4\n"
);

run(__LINE__,
"22\n"
"1 2 3 1 2 3 4 1 2 3 1 2 3 4 1 2 3 1 2 3 4 1\n"
,
"7\n"
);

run(__LINE__,
"13\n"
"5 3 1 3 5 2 5 3 1 3 5 2 5\n"
,
"6\n"
);

run(__LINE__,
"4\n"
"1 1 1 1\n"
,
"1\n"
);

run(__LINE__,
"4\n"
"1 2 3 1\n"
,
"3\n"
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
