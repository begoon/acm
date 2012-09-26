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

void print(ostream& os, const set<string>& s, const char* t) {
  os << t << ":";
  for (set<string>::const_iterator i = s.begin(); i != s.end(); ++i) {
    os << (i != s.begin() ? ", " : " ");
    os << *i;
  }
  os << endl;
}

int lengths[4] = { 1, 2, 3, 3 };

int find_best_filling(int p1, int p2, int m, vector<vector<int> >& room, vector<int>& cost, vector<vector<int> >& tile) {
}

void solve(istream& is, ostream& os) {
  int N, M, K;
  is >> N >> M >> K;
  vector<vector<int> > room(N, vector<int>(M, 0));
  for (int n = 0; n < N; ++n)
    for (int m = 0; m < M; ++m)
      is >> room[n][m];
  vector<int> cost(K), form(K);
  vector<vector<int> > tile(K, vector<int>());
  for (int k = 0; k < K; ++k) {
    is >> form[k] >> cost[k];
    for (int i = 0; i < lengths[form[k] - 1]; ++i) {
      int v;
      is >> v;
      tile[k].push_back(v);
    }
  }

  int dp[9][256][256];  // [i][P2][P]
  memset(dp, 0, sizeof(dp));

  for (int m = 0; m <= M; ++m) {
    for (int p1 = 0; p1 < (1 << N); ++p1) {
      for (int p2 = 0; p2 < (1<< N); ++p2) {
        int g = find_best_filling(p1, p2, m, room, cost, tile);
      }
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
      test >> ws;
      while (getline(test, line) && !line.empty())
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
