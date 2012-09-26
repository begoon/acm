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
  int T;
  is >> T;
  for (int t = 1; t <= T; ++t) {
    int N, L, H; is >> N >> L >> H;
    vector<int> v(N);
    for (int i = 0; i < N; ++i)
      is >> v[i];
    int freq = 0;
    for (int i = L; i <= H && freq == 0; ++i) {
      bool bad = false;
      for (int j = 0; j < N && !bad; ++j) {
        if (v[j] % i != 0 && i % v[j] != 0)
          bad = true;
      }
      if (!bad)
        freq = i;
    }
    os << "Case #" << t << ": ";
    if (freq)
      os << freq;
    else 
      os << "NO";
    os << std::endl;
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

  ifstream is("C.in");
  ofstream os("C.out");

  // istream& is = cin;
  // ostream& os = cout;
  
  solve(is, os);

#endif

#ifdef _DEBUG
  getchar();
#endif

  return 0;
}
