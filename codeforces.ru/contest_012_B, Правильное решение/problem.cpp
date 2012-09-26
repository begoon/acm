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

void solve(istream& is, ostream& os) {
  string a;
  getline(is, a);
  sort(a.begin(), a.end());
  if (a[0] == '0') {
  for (int i = 1; i < a.length(); ++i)
    if (a[i] != '0') {
      swap(a[0], a[i]);
      break;
    }
  }
  string b;
  getline(is, b);
  os << (a == b ? "OK" : "WRONG_ANSWER") << endl;
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
"1100\n"
"1001\n"
,
"OK\n"
);

run(__LINE__,
"210\n"
"102\n"
,
"OK\n"
);

run(__LINE__,
"1\n"
"1\n"
,
"OK\n"
);

run(__LINE__,
"10\n"
"10\n"
,
"OK\n"
);

run(__LINE__,
"3310\n"
"1033\n"
,
"OK\n"
);

run(__LINE__,
"4\n"
"5\n"
,
"WRONG_ANSWER\n"
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
