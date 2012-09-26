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

char get_char(istream& is) {
  char c;
  while (is.get(c) && isspace(c));
  return c;
}

int get_number(istream& is) {
  char c = get_char(is);
  bool minus = false;
  int n = 0;
  if (c == '-' || c == '+') {
    minus = c == '-';
    while (is.get(c) && isspace(c));
  }

  is.unget();

  while (is.get(c) && isdigit(c))
    n = n * 10 + c - '0';
  if (is) 
    is.unget();
  if (minus)
    n = -n;
  return n;
}

bool dfs(int etalon, int sum, bool& found, bool& empty, istream& is, ostream& os) {
  char c = get_char(is);  // (
  assert(c == '(');
  c = get_char(is);  // ) or one digit
  if (c == ')') 
    return true;   // empty leaf
  is.unget();
  int n = get_number(is);
  empty = false;
  bool left = dfs(etalon, sum + n, found, empty, is, os);
  bool right = dfs(etalon, sum + n, found, empty, is, os);
  if (left && right) {
    if (!found && !empty && sum + n == etalon) {
      found = true;
    }
  }
  c = get_char(is);  // )
  assert(c == ')');
  return false;
}

void solve(istream& is, ostream& os) {
  int etalon;
  while (is >> etalon) {
    bool found = false;
    bool empty = true;

    dfs(etalon, 0, found, empty, is, os);
    os << (found ? "yes" : "no") << endl;
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
      while (test >> line)
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

// ifstream is("input.txt");
// ofstream os("output.txt");

  istream& is = cin;
  ostream& os = cout;
  
  solve(is, os);

#endif

#ifdef _DEBUG
  getchar();
#endif

  return 0;
}
