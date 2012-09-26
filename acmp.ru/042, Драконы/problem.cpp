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

long long power(int t, int k) {
  long long r = 1;
  while (k) {
    if (k & 1) r *= t;
    t *= t;
    k >>= 1;
  }
  return r;
}

void solve(istream& is, ostream& os) {
  int n;
  is >> n;
  if (n <= 3) {
    os << n << endl;
    return;
  }
  int nb_3 = n / 3;
  int nb_2 = 0;
  int r = n % 3;
  switch (n % 3) {
    case 1:
      nb_3 -= 1;
      nb_2 = 2;
      break;
    case 2:
      nb_2 = 1;
      break;
  }
  os << power(3, nb_3) * power(2, nb_2) << endl;	
}

void solve_dp(istream& is, ostream& os) {
  int n;
  is >> n;
  vector<long long> dp(n + 1, -1);
  for (int i = 0; i <= n; ++i) {
    long long best = i;
    for (int j = 1; j <= i/2; ++j) {
      assert(dp[j] != -1);
      assert(dp[i-j] != -1);
      best = max(best, dp[j] * dp[i-j]);
    }
    dp[i] = best;
  }
  os << dp[n] << endl;
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
"6\n"
,
"9\n"
);

run(__LINE__,
"8\n"
,
"18\n"
);

run(__LINE__,
"13\n"
,
"108\n"
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
