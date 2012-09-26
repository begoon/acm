#include <iostream>
#include <vector>
#include <queue>
#include <set>
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
  int N;
  is >> N;
  vector<int> dp(N);
  for (int i = 0; i < N; ++i) {
    if (i == 0 || i == 1) 
      dp[i] = 1;
    else {
      dp[i] = dp[i-1] + 1;
      if (i >= 3)
        dp[i] += dp[i-3];
    }
  }
  os << dp[N-1] << endl;
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
"2\n"
,
"1\n"
);

run(__LINE__,
"3\n"
,
"2\n"
);

run(__LINE__,
"4\n"
,
"4\n"
);

run(__LINE__,
"5\n"
,
"6\n"
);

run(__LINE__,
"6\n"
,
"9\n"
);

run(__LINE__,
"7\n"
,
"14\n"
);

run(__LINE__,
"8\n"
,
"21\n"
);

run(__LINE__,
"9\n"
,
"31\n"
);

run(__LINE__,
"10\n"
,
"46\n"
);

run(__LINE__,
"11\n"
,
"68\n"
);

run(__LINE__,
"12\n"
,
"100\n"
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
