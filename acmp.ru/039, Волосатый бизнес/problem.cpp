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

void solve(istream& is, ostream& os) {
  int n;
  is >> n;
  vector<int> v(n);
  for (int i = 0; i < v.size(); ++i) is >> v[i];
  int ans = 0;
  int i = -1;
  do {
    int max_j = 0;
    int max = 0;
    for (int j = i + 1; j < v.size(); ++j)
      if (v[j] > max) {
        max = v[j];
        max_j = j;
      }
    ans += v[max_j] * (max_j - (i + 1) + 1);
    i = max_j;
  } while (i != v.size() - 1);
  os << ans << endl;
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
"5\n"
"73 31 96 24 46\n"
,
"380\n"
);

run(__LINE__,
"10\n"
"1 2 3 4 5 6 7 8 9 10\n"
,
"100\n"
);

run(__LINE__,
"10\n"
"10 9 8 7 6 5 4 3 2 1\n"
,
"55\n"
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

