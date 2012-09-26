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
using namespace std;

vector<vector<int> > dp;

int lsbra(const vector<string>& a, int x, int y) {
  if (x < 0 || y < 0) return 0;
  if (a[y][x] == '0') return 0;
  if (dp[y][x] != -1) return dp[y][x];
  if (x == 0 || y == 0) return 1;
  dp[y][x] = 1 + min(lsbra(a, x - 1, y), 
             min(lsbra(a, x, y - 1), lsbra(a, x - 1, y - 1)));
  return dp[y][x];
}

void solve_recursive(istream& is, ostream& os) {
  int N;
  is >> N >> ws;
  vector<string> f(N);
  for (int i = 0; i < N; ++i) {
    getline(is, f[i]);
  }
  dp = vector<vector<int> >(N, vector<int>(N, -1));
  int r = 0;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      int a = lsbra(f, x, y);
      a = a * a;
      if (a > r) r = a;
    }
  }
  os << r << endl;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N >> ws;
  vector<string> f(N);
  for (int i = 0; i < N; ++i) {
    getline(is, f[i]);
  }
  vector<vector<int> > dp(N, vector<int>(N, 0));
  int r = 0;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      if (f[y][x] == '0') continue;
      int left = x > 0 ? dp[y][x-1] : 0;
      int up = y > 0 ? dp[y-1][x] : 0;
      int diag = x > 0 && y > 0 ? dp[y-1][x-1] : 0;
      dp[y][x] = 1 + min(diag, min(left, up));
      int a = dp[y][x] * dp[y][x];
      if (a > r) r = a;
    }
  }
  os << r << endl;
}

const char* liner = "--------";

void run(int i, const char* input, const char* output) {
  stringstream is(input);
  stringstream os;
  solve(is, os);
  if (os.str() != output) {
    cerr << "Case #" << i << ": FAILED" << endl;
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else 
    cerr << "Case #" << i << " OK" << endl;
}

typedef vector< pair<const char*, const char*> > Cases;
void runner(Cases& cases, int i) {
  if (i != -1) run(i, cases[i].first, cases[i].second);
  else {
    for (int i = 0; i < cases.size(); ++i)
      run(i, cases[i].first, cases[i].second);
  }
}

Cases cases;

namespace {
// Needed to stupid Sun compiler.
pair<const char*, const char*> make_pair(const char* a, const char* b) {
  return std::make_pair(a, b);
}
}

int main(int argc, char* argv[]) {
#ifdef TESTING_
cases.push_back(make_pair(
"7\n"
"1101101\n"
"1111110\n"
"1010100\n"
"0011100\n"
"1000010\n"
"1100111\n"
"1001110\n"
,
"4\n"
));
cases.push_back(make_pair(
"7\n"
"1101101\n"
"1111110\n"
"1011100\n"
"0011100\n"
"1000010\n"
"1100111\n"
"1001110\n"
,
"9\n"
));
cases.push_back(make_pair(
"2\n"
"00\n"
"10\n"
,
"1\n"
));
cases.push_back(make_pair(
"2\n"
"00\n"
"00\n"
,
"0\n"
));
cases.push_back(make_pair(
"2\n"
"11\n"
"11\n"
,
"4\n"
));
cases.push_back(make_pair(
"1\n"
"1\n"
,
"1\n"
));
cases.push_back(make_pair(
"1\n"
"0\n"
,
"0\n"
));
cases.push_back(make_pair(
"4\n"
"1111\n"
"1011\n"
"1111\n"
"1111\n"
,
"4\n"
));
cases.push_back(make_pair(
"4\n"
"1111\n"
"1111\n"
"1111\n"
"1111\n"
,
"16\n"
));
cases.push_back(make_pair(
"2\n"
"00\n"
"01\n"
,
"1\n"
));
cases.push_back(make_pair(
"2\n"
"01\n"
"00\n"
,
"1\n"
));
cases.push_back(make_pair(
"2\n"
"10\n"
"00\n"
,
"1\n"
));
cases.push_back(make_pair(
"2\n"
"01\n"
"10\n"
,
"1\n"
));
cases.push_back(make_pair(
"4\n"
"1011\n"
"1111\n"
"1111\n"
"1111\n"
,
"9\n"
));

runner(cases, -1);
getchar();

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
solve(is, os);

#endif

}

