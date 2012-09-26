#include <iostream>
#include <vector>
#include <stack>
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
#include <cassert>
using namespace std;

template <typename T>
ostream& print(const T& a, bool eol = true) {
  copy(a.begin(), a.end(), ostream_iterator<typename T::value_type>(cerr, " "));
  if (eol) cerr << endl;
  return cerr;
}

ostream& print(const vector<vector<int> >& a, int w = 2) {
  for (int i = 0; i < a.size(); ++i) {
    cerr << setw(2) << i << ": ";
    print(a[i]);
  }
  return cerr;
}

void solve(istream& is, ostream& os) {
  int N;
  is >> N >> ws;
  vector<int> v(N);
  for (int i = 0; i < N; ++i) is >> v[i];

  int r = 0;
  sort(v.begin(), v.end());

  vector<int> d(N + 1, 0);
  d[0] = 0;
  d[1] = numeric_limits<int>::max();
  for (int i = 0; i < N - 1; ++i)
    d[2 + i] = min(d[2 + (i-2)], d[2 + (i-1)]) + v[i + 1] - v[i];

  r = d[N];
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
// Needed for stupid Sun compiler.
pair<const char*, const char*> make_pair(const char* a, const char* b) {
  return std::make_pair(a, b);
}
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

cases.push_back(make_pair(
"6\n"
"3 4 6 12 13 14\n"
,
"5\n"
));

cases.push_back(make_pair(
"4\n"
"1 2 9999 10000\n"
,
"2\n"
));

cases.push_back(make_pair(
"2\n"
"2 1\n"
,
"1\n"
));

cases.push_back(make_pair(
"6\n"
"3 4 12 6 14 13\n"
,
"5\n"
));

cases.push_back(make_pair(
"6\n"
"1 2 4 7 11 16\n"
,
"9\n"
));

cases.push_back(make_pair(
"7\n"
"6 10 3 7 19 20 21\n"
,
"8\n"
));

cases.push_back(make_pair(
"7\n"
"3 6 7 10 19 20 21\n"
,
"8\n"
));

cases.push_back(make_pair(
"7\n"
"6 3 7 10 15 20 21\n"
,
"10\n"
));

cases.push_back(make_pair(
"7\n"
"3 6 7 10 15 20 21\n"
,
"10\n"
));

cases.push_back(make_pair(
"8\n"
"7 2 3 6 8 9 12 15\n"
,
"6\n"
));

cases.push_back(make_pair(
"8\n"
"2 3 6 7 8 9 12 15\n"
,
"6\n"
));

cases.push_back(make_pair(
"5\n"
"1 5 6 7 8\n"
,
"6\n"
));

cases.push_back(make_pair(
"10\n"
"10682 2517 2478 2816 4980 5839 6414 7667 8802 8995\n"
,
"4330\n"
));

runner(cases, -1);
getchar();

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
solve(is, os);

#endif

}

