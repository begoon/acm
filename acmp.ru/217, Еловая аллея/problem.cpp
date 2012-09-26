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

void solve(istream& is, ostream& os) {
  int M;
  is >> M;
  vector<int> w(M), e(M);
  for (int i = 0; i < M; ++i)
    is >> w[i] >> e[i];

  int N;
  is >> N;
  vector<int> p(N);
  for (int i = 0; i < N; ++i)
    is >> p[i];

  vector<vector<int> > dp(M, vector<int>(N, 0));

  for (int i = 0; i < M; ++i)
    dp[i][0] = 1;
       
  for (int i = 1; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      for (int i0 = 0; i0 < i; ++i0) {
        for (int j0 = 0; j0 < M; ++j0) {
          if (p[i0] + e[j0] <= p[i] && p[i] - w[j] >= p[i0])
            dp[j][i] = max(dp[j][i], dp[j0][i0] + 1);
        }
      }
    }
  }

  int ans = 0;

  for (int i = 0; i < M; ++i)
    for (int j = 0; j < N; ++j)
      ans = max(ans, dp[i][j]);

  os << ans << endl;
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
