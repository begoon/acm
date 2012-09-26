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

const int M = 1000;

void solve(istream& is, ostream& os) {
  int T;
  is >> T >> ws;
  for (int t = 0; t < T; ++t) {
    vector<int> m(M, 0);
    vector<int> r(10, 0);
    int ip = 0;
    while (true) {
      string l;
      getline(is, l);
      if (l.empty()) break;
      m[ip] = std::atoi(l.c_str());
      ip += 1;
    }
    ip = 0;
    int cycles = 0;
    bool halt = false;
    while (!halt) {
      cycles += 1;
      int op = m[ip];
      ip = (ip + 1) % M;
      int cmd = (op / 100) % 10;
      int a1 = (op / 10) % 10;
      int a2 = op % 10;
      assert(cmd * 100 + a1 * 10 + a2 == op);
      switch (cmd) {
        case 1: halt = true; break;
        case 2: r[a1] = a2; break;
        case 3: r[a1] = (r[a1] + a2) % M; break;
        case 4: r[a1] = (r[a1] * a2) % M; break;
        case 5: r[a1] = r[a2]; break;
        case 6: r[a1] = (r[a1] + r[a2]) % M; break;
        case 7: r[a1] = (r[a1] * r[a2]) % M; break;
        case 8: r[a1] = m[r[a2]]; break;
        case 9: m[r[a2]] = r[a1]; break;
        case 0: ip = r[a2] ? r[a1] : ip; break;
      }
    }
    os << cycles << endl;
    if (t < T - 1) os << endl;
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
"1\n"
"\n"
"299\n"
"492\n"
"495\n"
"399\n"
"492\n"
"495\n"
"399\n"
"283\n"
"279\n"
"689\n"
"078\n"
"100\n"
"000\n"
"000\n"
"000\n"
,
"16\n"
);

run(__LINE__,
"2\n"
"\n"
"299\n"
"492\n"
"495\n"
"399\n"
"492\n"
"495\n"
"399\n"
"283\n"
"279\n"
"689\n"
"078\n"
"100\n"
"000\n"
"000\n"
"000\n"
"\n"
"299\n"
"492\n"
"495\n"
"399\n"
"492\n"
"495\n"
"399\n"
"283\n"
"279\n"
"689\n"
"078\n"
"100\n"
"000\n"
"000\n"
"000\n"
,
"16\n\n"
"16\n"
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
