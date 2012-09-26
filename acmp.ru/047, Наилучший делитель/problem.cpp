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

void solve(istream& is, ostream& os) {
  int a;
  is >> a;
  vector<int> f;
  f.push_back(1);
  for (int i = 2; i <= sqrt((double)a); ++i) {
    if (a % i == 0) {
      f.push_back(i);
      if (a/i != i)
        f.push_back(a / i);
    }
  }
  f.push_back(a);
  vector<int> s(f.size(), 0);
  for (int i = 0; i < f.size(); ++i) {
    int t = f[i];
    while (t > 0) {
      s[i] += t % 10;
      t /= 10;
    }
  }
  int max = *max_element(s.begin(), s.end());
  int min = numeric_limits<int>::max();
  for (int i = 0; i < s.size(); ++i)
    if (s[i] == max) 
      if (f[i] < min)
        min = f[i];
      
  os << min << endl;
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
"10\n"
,
"5\n"
);

run(__LINE__,
"239\n"
,
"239\n"
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

