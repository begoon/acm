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

void solve_quicksort(istream& is, ostream& os) {
  int n;
  is >> n;
  vector<int> v(201, 0);
  for (int i = 0; i < v.size(); ++i) {
    int t;
    is >> t;
    v[t + 100] += 1;
  }
  for (int i = 0; i < v.size(); ++i)
    for (int j = 0; j < v[i]; ++j) {
      if (i > 0 || j > 0) os << " ";
      os << j - 100;
    }
  os << endl;
}

void solve(istream& is, ostream& os) {
  int n;
  is >> n;
  vector<int> v(n);
  for (int i = 0; i < v.size(); ++i) is >> v[i];
  sort(v.begin(), v.end());
  for (int i = 0; i < v.size(); ++i) {
    if (i > 0) os << " ";
    os << v[i];
  }
  os << endl;
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
"9 -20 14\n"
,
"-20 9 14\n"
);

run(__LINE__,
"10\n"
"12 7 92 5 18 4 32 48 11 74\n"
,
"4 5 7 11 12 18 32 48 74 92\n"
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

