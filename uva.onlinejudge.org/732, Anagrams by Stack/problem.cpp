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

#define int_ long long

int found = 0;

void anagram(istream& is, ostream& os, string s1, string s2, string q, string cmd) {
  if (s2.empty()) {
    if (s1.empty() && q.empty())
      os << cmd.substr(0, cmd.find_last_not_of(" ") + 1) << std::endl;
    return;
  }
  if (!s1.empty())
    anagram(is, os, s1.substr(1), s2, s1.substr(0, 1) + q, cmd + "i ");
  if (!q.empty() && q[0] == s2[0])
    anagram(is, os, s1, s2.substr(1), q.substr(1), cmd + "o ");
}

void anagram(istream& is, ostream& os, std::string s1, std::string s2) {
  os << "[" << std::endl;
  anagram(is, os, s1, s2, "", "");
  os << "]" << std::endl;
}

void solve(istream& is, ostream& os) {
  while (is) {
    string s1, s2;
    getline(is, s1);
    getline(is, s2);
    if (!is || s1.empty() || s2.empty()) break;
    anagram(is, os, s1, s2);
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
"madam\n"
"adamm\n"
"bahama\n"
"bahama\n"
"long\n"
"short\n"
"eric\n"
"rice\n"
,
"[\n"
"i i i i o o o i o o\n"
"i i i i o o o o i o\n"
"i i o i o i o i o o\n"
"i i o i o i o o i o\n"
"]\n"
"[\n"
"i o i i i o o i i o o o\n"
"i o i i i o o o i o i o\n"
"i o i o i o i i i o o o\n"
"i o i o i o i o i o i o\n"
"]\n"
"[\n"
"]\n"
"[\n"
"i i o i o i o o\n"
"]\n"
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

