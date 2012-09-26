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

#define __int64 long long

bool extact_sqrt(__int64 n) {
  __int64 i = floor(sqrt((double)n) + 0.5);
  return i * i == n;
}

int nb_dividers(__int64 N) {
  int a = 1;
  for (__int64 i = 2; i*i <= N; ++i) {
    if (N % i) continue;
    int c = 0;
    while ((N % i) == 0) {
      c += 1;
      N /= i;
    }
    a *= c + 1;
  }
  if (N > 1)
    a *= 2;
  return a;
}

int f(__int64 N) {
  __int64 r = 1;
  __int64 t = N;

  for (__int64 i = 2; i*i <= t; ++i) {
    if (t % i) continue;
    r *= i;
    while ((t % i) == 0)
      t /= i;
  }
  if (t > 1)
    r *= t;

  N /= r;

  return nb_dividers(N);
}

void solve(istream& is, ostream& os) {
  unsigned __int64 N;
  is >> N;

  os << f(N) << endl;
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
"45\n"  // 15 * 3 = 5 * 3 * 3
,
"2\n"
);

run(__LINE__,
"100\n"
,
"4\n"
);

run(__LINE__,
"40\n"
,
"3\n"
);

run(__LINE__,
"2000000000000000000\n"
,
"342\n"
);

run(__LINE__,
"7948710\n"
,
"2\n"
);

run(__LINE__,
"101\n"
,
"1\n"
);

run(__LINE__,
"1\n"
,
"1\n"
);

run(__LINE__,
"2\n"
,
"1\n"
);

run(__LINE__,
"3\n"
,
"1\n"
);

run(__LINE__,
"4\n"
,
"2\n"
);

run(__LINE__,
"5\n"
,
"1\n"
);

run(__LINE__,
"6\n"
,
"1\n"
);

run(__LINE__,
"12\n"
,
"2\n"
);

run(__LINE__,
"239\n"
,
"1\n"
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
