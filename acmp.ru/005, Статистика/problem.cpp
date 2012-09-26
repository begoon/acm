#include <iostream>
#include <vector>
#include <queue>
#include <set>
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

void solve(istream& is, ostream& os) {
  int N;
  is >> N;
  vector<int> m(N);
  for (int i = 0; i < N; ++i) is >> m[i];
  int odd = 0;
  bool first = true;
  for (int i = 0; i < N; ++i) {
    if (m[i] & 1) {
      odd += 1;
      if (!first) os << " ";
      os << m[i];
      first = false;
    }
  }
  os << endl;
  int even = 0;
  first = true;
  for (int i = 0; i < N; ++i) {
    if ((m[i] & 1) == 0) {
      even += 1;
      if (!first) os << " ";
      os << m[i];
      first = false;
    }
  }
  os << endl;
  os << (even >= odd ? "YES" : "NO") << endl;
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
"4 16 19 31 2\n"
,
"19 31\n"
"4 16 2\n"
"YES\n"
);

run(__LINE__,
"8\n"
"29 4 7 12 15 17 24 1\n"
,
"29 7 15 17 1\n"
"4 12 24\n"
"NO\n"
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
