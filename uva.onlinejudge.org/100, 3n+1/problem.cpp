#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <limits>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

int cycle(unsigned int a, vector<unsigned int>& u) {
  int l = 1;
  if (a == 0 || a == 1) return a;
  while (a > 1) {
    if (a < u.size() && u[a]) {
      l += u[a] - 1;
      break;
    }
    l += 1;
    a = a & 1 ? a*3+1 : a/2;
  }
  return l;
}

const int L = 1000000;

void solve(istream& is, ostream& os) {
  unsigned int a0, b0;
  vector<unsigned int> u(L + 1, 0);
  while (is >> a0 >> b0) {
    unsigned int m = 0;
    unsigned int a = min(a0, b0);
    unsigned int b = max(a0, b0);
    for (unsigned int i = 1; i <= b; ++i) {
      u[i] = cycle(i, u);
      if (i >= a && u[i] > m) m = u[i];
    }
    os << a0 << " " << b0 << " " << m << endl;
  }
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
"1 999999\n"
,
"1 999999 525\n"
);

run(__LINE__,
"1 10\n"
,
"1 10 20\n"
);

run(__LINE__,
"100 200\n"
,
"100 200 125\n"
);

run(__LINE__,
"201 210\n"
,
"201 210 89\n"
);

run(__LINE__,
"900 1000\n"
,
"900 1000 174\n"
);

run(__LINE__,
"1000 900\n"
,
"1000 900 174\n"
);

run(__LINE__,
"1 10\n"
"100 200\n"
"201 210\n"
"900 1000\n"
,
"1 10 20\n"
"100 200 125\n"
"201 210 89\n"
"900 1000 174\n"
);

#ifdef _DEBUG
getchar();
#endif

#else

// ifstream is("INPUT.TXT");
// ofstream os("OUTPUT.TXT");
istream& is = cin;
ostream& os = cout;

solve(is, os);

#endif

return 0;
}
