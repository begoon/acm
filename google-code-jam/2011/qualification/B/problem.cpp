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

#undef min
#undef max
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

void solve(istream& is, ostream& os) {
  int N;
  is >> N;
  for (int n = 1; n <= N; ++n) {
    int u;

    map<char, map<char, char> > combined;
    is >> u;
    while (u--) {
      string s;
      is >> s;
      combined[s[0]][s[1]] = s[2];
      combined[s[1]][s[0]] = s[2];
    }

    map<char, map<char, char> > opposed;
    is >> u;
    while (u--) {
      string s;
      is >> s;
      opposed[s[0]][s[1]] = 1;
      opposed[s[1]][s[0]] = 1;
    }

    string to_invoke;
    is >> u >> to_invoke;
    assert(u == to_invoke.length());

    string r;

    map<char, int> seen;
    for (string::const_iterator i = to_invoke.begin(); i != to_invoke.end(); ++i) {
      if (r.length() == 0) {
        r += *i;
        seen[*i] += 1;
      } else {
        char c = combined[*i][r.back()];
        if (c != 0) {
          if (seen[*i] > 0)
            seen[*i] -= 1;
          if (seen[r.back()] > 0)
            seen[r.back()] -= 1;
          r.back() = c;
        } else {
          r += *i;
          seen[*i] += 1;
          for (map<char, int>::const_iterator j = seen.begin(); j != seen.end(); ++j) {
            if (j->second > 0 && opposed[j->first][*i]) {
              r.clear();
              seen.clear();
              break;
            }
          }
        }
      }
    }

    string list = "[";
    for (string::const_iterator i = r.begin(); i != r.end(); ++i) {
      if (i != r.begin())
        list += ", ";
      list += *i;
    }
    list += "]";

    os << "Case #" << n << ": " << list << std::endl;
  }
}

#ifdef int
#undef int
#endif

#include <ctime>

void run(const string& test_name, const char* input, const char* output) {
  const char* liner = "--------";
  stringstream is(input);
  stringstream os;
  clock_t started = clock();
  solve(is, os);
  clock_t elapsed = clock() - started;
  if (os.str() != output) {
    cerr << "Case '" << test_name << "': FAILED" << endl;
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else {
    cerr << "Case '" << test_name << "': OK";
    if (elapsed > CLOCKS_PER_SEC / 200)
      cerr << " time " << elapsed * (1.0/CLOCKS_PER_SEC) << "s";
    cerr << endl;
  }
}

void run_test(const string& test_name) {
  ifstream test(test_name.c_str(), ifstream::in);
  string input, output;
  string line;
  while (getline(test, line)) {
    if (line.substr(0, 5) == "~~~~~") {
      while (getline(test, line))
        output += line + "\n";
    } else {
      input += line + "\n";
    }
  }
  run(test_name, input.c_str(), output.c_str());
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

  string test_name; // = "test0.tst";

  if (!test_name.empty()) {
    run_test(test_name);  
  } else {
    if (system("cmd /c dir /on /b *.tst >tests.lst")) {
      cerr << "error: unable to find tests" << endl;
      exit(1);
    }
    ifstream tests("tests.lst", ifstream::in);

    while (tests >> test_name) {
      if (test_name.empty()) continue;
      run_test(test_name);
    }
  }

#else

  ifstream is("B.in");
  ofstream os("B.out");

  // istream& is = cin;
  // ostream& os = cout;
  
  solve(is, os);

#endif

#ifdef _DEBUG
  getchar();
#endif

  return 0;
}
