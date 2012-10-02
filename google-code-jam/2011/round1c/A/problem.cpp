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

vector<string> solution;
int R, C; 

int search(vector<string>& m, int rr, int cc) {
  for (int r = rr; r < R; ++r) {
    for (int c = cc; c < C; ++c) {
      if (m[r][c] == '.') continue;
      if (m[r][c] == '/' || m[r][c] == '\\') continue;
      assert(m[r][c] == '#');
      if (r == R - 1 || c == C - 1 ||
          m[r + 1][c] != '#' ||
          m[r][c + 1] != '#' ||
          m[r + 1][c + 1] != '#') {
        return 1;
      }
      m[r][c] = '/'; m[r][c + 1] = '\\'; m[r + 1][c] = '\\'; m[r + 1][c + 1] = '/';
      int t = search(m, r, c + 2);
      if (t != 0) return t;
      assert(0);
      m[r][c] = m[r][c + 1] = m[r + 1][c] = m[r + 1][c + 1] = '#';
    }
    cc = 0;
  }
  solution = m;
  return 2;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N;
  for (int n = 1; n <= N; ++n) {
    is >> R >> C;
    vector<string> m(R, string(C, 0));
    for (int r = 0; r < R; ++r) {
      is >> m[r];
    }
    solution.clear();
    search(m, 0, 0);
    os << "Case #" << n << ":" << std::endl;
    if (solution.empty()) 
      os << "Impossible" << endl;
    else {
      assert(solution.size() == R);
      for (int i = 0; i < R; ++i)
        os << solution[i] << endl;
    }
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

  ifstream is("A.in");
  ofstream os("A.out");

  // istream& is = cin;
  // ostream& os = cout;
  
  solve(is, os);

#endif

#ifdef _DEBUG
  getchar();
#endif

  return 0;
}