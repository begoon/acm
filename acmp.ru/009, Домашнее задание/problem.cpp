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

void solve(istream& is, ostream& os) {
  int N;
  is >> N;
  vector<int> v(N);
  for (int i = 0; i < v.size(); ++i) is >> v[i];
  int s = 0;
  int min_i = -1;
  int min = numeric_limits<int>::max();
  int max_i = -1;
  int max = numeric_limits<int>::min();
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] > 0)
      s += v[i];
    if (v[i] < min) {
      min = v[i];
      min_i = i;
    }
    if (v[i] > max) {
      max = v[i];
      max_i = i;
    } 
  }
  assert(min_i != -1);
  assert(max_i != -1);
  int p = 1;
  if (min_i > max_i) swap(min_i, max_i);
  for (int i = min_i + 1; i < max_i; ++i)
    p *= v[i];
  os << s << " " << p << endl;
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
"-7 5 -1 3 9\n"
,
"17 -15\n"
);

run(__LINE__,
"8\n"
"3 14 -9 4 -5 1 -12 4\n"
,
"26 180\n"
);

run(__LINE__,
"10\n"
"-5 1 2 3 4 5 6 7 8 -3\n"
,
"36 5040\n"
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
