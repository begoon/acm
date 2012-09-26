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

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

void solve(istream& is, ostream& os) {
  int E, F;
  is >> E >> F;
  int C = F - E;

  int N;
  is >> N;

  vector<int> value(N);
  vector<int> weight(N);

  for (int i = 0; i < N; ++i) {
    is >> value[i] >> weight[i];
  }

  vector<int> dp_max(C + 1, numeric_limits<int>::min());
  vector<int> dp_min(C + 1, numeric_limits<int>::max());

  dp_max[0] = dp_min[0] = 0;

  for (int i = 1; i <= C; ++i) {
    for (int t = 0; t < N; ++t) {
      int j = i - weight[t];
      if (j < 0) continue;
      if (dp_max[j] != numeric_limits<int>::min()) {
        dp_max[i] = max(dp_max[i], dp_max[j] + value[t]);
      }
      if (dp_min[j] != numeric_limits<int>::max()) {
        dp_min[i] = min(dp_min[i], dp_min[j] + value[t]);
      }
    }
  }

  if (dp_max[C] == numeric_limits<int>::min() || dp_min[C] == numeric_limits<int>::max())
    os << "This is impossible." << endl;
  else
    os << dp_min[C] << " " << dp_max[C] << endl;
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

  ifstream is("input.txt");
  ofstream os("output.txt");

  // istream& is = cin;
  // ostream& os = cout;
  
  solve(is, os);

#endif

#ifdef _DEBUG
  getchar();
#endif

  return 0;
}
