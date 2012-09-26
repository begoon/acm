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

void solve(istream& is, ostream& os) {
  vector<string> t;
  size_t m = 0;
  while (is) {
    string s;
    getline(is, s);
    if (s.empty() && !is) break;
    t.push_back(s);
    m = max(m, s.length());
  }
  os << string(m + 2, '*') << endl;
  int f = 0;
  for (int i = 0; i < t.size(); ++i) {
    int l = t[i].size();
    int o = (m - l) / 2;
    int left = o, right = o;
    if ((m - l) & 1) {
      left += f;
      right += f ^ 1;
      f ^= 1;
    }
    os << "*" << string(left, ' ') << t[i] << string(right, ' ') << "*" << endl;
  }
  os << string(m + 2, '*') << endl;
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
"\n"
"\n"
,
"***\n"
"*1*\n"
"* *\n"
"* *\n"
"* *\n"
"***\n"
);

run(__LINE__,
"This  is\n"
"\n"
"Codeforces\n"
"Beta\n"
"Round\n"
"5\n"
,
"************\n"
"* This  is *\n"
"*          *\n"
"*Codeforces*\n"
"*   Beta   *\n"
"*  Round   *\n"
"*     5    *\n"
"************\n"
);

run(__LINE__,
"welcome to the\n"
"Codeforces\n"
"Beta\n"
"Round 5\n"
"\n"
"and\n"
"good luck\n"
,
"****************\n"
"*welcome to the*\n"
"*  Codeforces  *\n"
"*     Beta     *\n"
"*   Round 5    *\n"
"*              *\n"
"*      and     *\n"
"*  good luck   *\n"
"****************\n"
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
