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
  int n;
  while (is) {
    vector<int> v(9);
    for (int i = 0; i < v.size(); ++i) is >> v[i];
    if (!is) break;
    string p = "BCG";
    string r = "?";
    int m = numeric_limits<int>::max();
    do {
      int s = 0;
      for (int i = 0; i < 3; ++i) {
        int j = p[i] == 'B' ? 0 : (p[i] == 'G' ? 1 : 2);
        s += v[((i + 1) * 3 + j) % 9] + v[((i + 2) * 3 + j) % 9];
      }
      if (s < m) {
        m = s;
        r = p;
      }
    } while (next_permutation(p.begin(), p.end()));
    assert(r != "?");
    os << r << " " << m << endl;
  }
}

const char* liner = "--------";
int problem;
int problem_filter;

#ifdef int
#undef int
#endif

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
"1 2 3 4 5 6 7 8 9\n"
"5 10 5 20 10 5 10 20 10\n"
,
"BCG 30\n"
"CBG 50\n"
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

