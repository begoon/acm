#include <iostream>
#include <vector>
#include <map>
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
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

void solve(istream& is, ostream& os) {
  int N;
  is >> N >> ws;

  vector<vector<long long> > d(N, vector<long long>(N, 0));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) d[i][j] = 0;
    d[i][i] = 1;
  }
  for (int i = 1; i < N; ++i) {
    for (int j = i - 1; j >= 0; --j)
      d[i][j] = d[i-j-1][j+1] + d[i][j+1];
  }

  os << d[N-1][0]-1 << endl;
}

const char* liner = "--------";
static int problem = 0;
static int problem_filter = -1;

void run(int line, const char* input, const char* output) {
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
  problem += 1;
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

int problem = 0;

run(__LINE__,
"5\n"
,
"2\n"
);

run(__LINE__,
"212\n"
,
"995645335\n"
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

}
