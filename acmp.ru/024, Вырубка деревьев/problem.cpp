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

void solve_simple(istream& is, ostream& os) {
  int N, M;
  is >> N >> M;

  int r;
  if (M == 0)
    r = 1;
  else if (M == 1)
    r = N;
  else {
    int p = 0;
    r = 0;
    while (true) {
      int d = M + (M-1)*p;
      if (d > N) break;
      r += N - d + 1;
      p += 1; 
    }
  }
  os << r << endl;
}

void solve(istream& is, ostream& os) {
  int N, M;
  is >> N >> M;

  int r;
  if (M == 0)
    r = 1;
  else if (M == 1)
    r = N;
  else {
    int l = (N-M) / (M-1);
    r = (N - M + 1) * (l + 1) - (M-1) * l * (l + 1)/2;
  }
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
"5 0\n"
,
"1\n"
);

run(__LINE__,
"5 1\n"
,
"5\n"
);

run(__LINE__,
"5 3\n"
,
"4\n"
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
