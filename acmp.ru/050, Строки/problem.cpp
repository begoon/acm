#include <iostream>
#include <vector>
#include <map>
#include <set>
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

void solve(istream& is, ostream& os) {
  string a, b;
  getline(is, a);
  getline(is, b);

  set<string> m;
  for (int i = 0; i < b.length(); ++i) {
    string s = b.substr(i, b.length() - i) + b.substr(0, i);
    m.insert(s);
  }

  int r = 0;
  for (int i = 0; i < a.length(); ++i) {
    for (set<string>::iterator j = m.begin(); j != m.end(); ++j)
      if (j->length() <= a.length() - i && a.substr(i, j->length()) == *j)
        r += 1;
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
"abcabc\n"
"abc\n"
,
"4\n"
);

run(__LINE__,
"abcabc\n"
"acb\n"
,
"0\n"
);

run(__LINE__,
"aaaaaaa\n"
"aa\n"
,
"6\n"
);

run(__LINE__,
"aAaa8aaAa\n"
"aAa\n"
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
