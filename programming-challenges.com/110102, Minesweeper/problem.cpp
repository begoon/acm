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
#include <cassert>
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

void solve(istream& is, ostream& os) {
  int N, M;
  int f = 1;
  while (true) {
    is >> N >> M >> ws;
    if (N == 0 && M == 0) return;
    if (f > 1) os << endl;
    os << "Field #" << f << ":" << endl;
    f += 1;
    vector<string> a(N);
    for (int i = 0; i < N; ++i)
      getline(is, a[i]);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if (a[i][j] == '*') 
          os << '*';
        else {
          int m = 0;
          if (i > 0 && j > 0)     m += a[i-1][j-1] == '*';
          if (i > 0)              m += a[i-1][j  ] == '*';
          if (i > 0 && j < M-1)   m += a[i-1][j+1] == '*';
          if (i < N-1 && j > 0)   m += a[i+1][j-1] == '*';
          if (i < N-1)            m += a[i+1][j  ] == '*';
          if (i < N-1 && j < M-1) m += a[i+1][j+1] == '*';
          if (j > 0)              m += a[i  ][j-1] == '*';
          if (j < M-1)            m += a[i  ][j+1] == '*';
          os << m;
        }
      }
      os << endl;
    }
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
"4 4\n"
"*...\n"
"....\n"
".*..\n"
"....\n"
"3 5\n"
"**...\n"
".....\n"
".*...\n"
"0 0\n"
,
"Field #1:\n"
"*100\n"
"2210\n"
"1*10\n"
"1110\n"
"\n"
"Field #2:\n"
"**100\n"
"33200\n"
"1*100\n"
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
