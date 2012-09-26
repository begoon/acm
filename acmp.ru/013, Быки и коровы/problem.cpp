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

template <typename T>
T triangle_area_2(T x1, T y1, T x2, T y2, T x3, T y3) {
  return (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
}

void solve(istream& is, ostream& os) {
  string s;
  getline(is, s);
  int bulls = 0, cows = 0;
  for (int i = 0; i < 4; ++i)
    if (s[i + 5] == s[i]) {
      bulls += 1;
      s[i] = s[i + 5] = '.';
    }
  for (int i = 0; i < 4; ++i)
    if (s[i + 5] != '.')
      for (int j = 0; j < 4; ++j)
        if (s[j] != '.')
          if (s[i + 5] == s[j]) {
            cows += 1;
            s[i + 5] = s[j] = '.';
            break;
          }
  os << bulls << " " << cows << endl;
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
"5671 7251\n"
,
"1 2\n"
);

run(__LINE__,
"1234 1234\n"
,
"4 0\n"
);

run(__LINE__,
"2034 6234\n"
,
"2 1\n"
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
