#include <iostream>
#include <vector>
#include <map>
#include <deque>
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

int as_bits(char ch) {
  switch (ch) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': return 1 << (ch - '0');
    case 'a': return 0x0F;
    case 'b': return 0x0F << 1;
    case 'c': return 0x0F << 2;
    case 'd': return 0x0F << 3;
    case 'e': return 0x0F << 4;
    case 'f': return 0x0F << 5;
    case 'g': return 0x0F << 6;
    case '?': return (1 << 10) - 1;
  }
  assert(0);
}

int nb_bits(int n) {
  int r = 0;
  while (n) {
    n &= (n - 1);
    ++r;
  }
  return r;
}

void solve(istream& is, ostream& os) {
  string a, b;
  is >> a >> b;

  int c = 1;
  for (int i = 0; i < a.length(); ++i) {
    int x = as_bits(a[i]);
    int y = as_bits(b[i]);
    int r = x & y;
    c *= nb_bits(r);
  }
  os << c << endl;
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
"???\n"
"abc\n"
,
"64\n"
);

run(__LINE__,
"???\n"
"000\n"
,
"1\n"
);

run(__LINE__,
"abc\n"
"999\n"
,
"0\n"
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
