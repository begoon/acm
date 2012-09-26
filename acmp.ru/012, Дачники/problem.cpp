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

template <typename T>
T sqr(T a) {
  return a * a;
}

const double EPS = 1e-9;

template <typename T>
T triangle_area_2(T x1, T y1, T x2, T y2, T x3, T y3) {
  return (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;
  int cnt = 0;
  for (int n = 0; n < N; ++n) {
    long long x, y, x1, y1, x2, y2, x3, y3, x4, y4;
    is >> x >> y >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    long long s1 = triangle_area_2(x1, y1, x2, y2, x, y);
    long long s2 = triangle_area_2(x2, y2, x3, y3, x, y);
    long long s3 = triangle_area_2(x3, y3, x4, y4, x, y);
    long long s4 = triangle_area_2(x4, y4, x1, y1, x, y);
    if (s1 >= 0 && s2 >= 0 && s3 >= 0 && s4 >= 0 ||
        s1 <= 0 && s2 <= 0 && s3 <= 0 && s4 <= 0)
      cnt += 1;
  }
  os << cnt << endl;
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
"3\n"
"6 6 3 6 6 9 8 7 5 4\n"
"13 5 9 2 9 8 12 8 12 2\n"
"3 2 2 1 2 3 6 3 6 1\n"
,
"2\n"
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
