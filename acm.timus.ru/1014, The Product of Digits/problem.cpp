#include <iostream>
#include <vector>
#include <map>
#include <set>
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
#include <cassert>
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

void solve(istream& is, ostream& os) {
  unsigned int N;
  is >> N;
  multiset<unsigned int> s;
  if (N == 0) {
    os << 10 << endl;
    return;
  }
  if (N == 1) {
    os << 1 << endl;
    return;
  }
  for (int i = 9; i >= 2; --i) {
    while (N % i == 0) {
      s.insert(i);
      N /= i;
    }
  }
  if (N > 1) {
    os << -1 << endl;
  } else {
    for (multiset<unsigned int>::const_iterator i = s.begin(); i != s.end(); ++i)
      os << *i;
    os << endl;
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
"1\n"
,
"1\n"
);

run(__LINE__,
"0\n"
,
"10\n"
);

run(__LINE__,
"10\n"
,
"25\n"
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
