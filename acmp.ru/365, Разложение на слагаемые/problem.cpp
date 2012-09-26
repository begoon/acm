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

void f(ostream& os, vector<int>& sum, int step, int min, int left) {
  // If i <= left/2 in the loop this boundary case never happens.
  // if (min > left) return;

  if (step > 0) {
    copy(sum.begin(), sum.begin() + step, ostream_iterator<int>(os, "+"));
    os << left << endl;
  }
  for (int i = min; i <= left / 2; ++i) {
    sum[step] = i;
    f(os, sum, step + 1, i, left - i);
  }
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;

  vector<int> sum(N, 0);
  f(os, sum, 0, 1, N);
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
"4\n"
,
"1+3\n"
"1+1+2\n"
"1+1+1+1\n"
"2+2\n"
);

run(__LINE__,
"5\n"
,
"1+4\n"
"1+1+3\n"
"1+1+1+2\n"
"1+1+1+1+1\n"
"1+2+2\n"
"2+3\n"
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
