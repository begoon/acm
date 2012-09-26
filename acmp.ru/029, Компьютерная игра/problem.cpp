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

void solve(istream& is, ostream& os) {
  int N;
  is >> N >> ws;
  vector<int> f(N);
  for (int i = 0; i < N; ++i) is >> f[i];

  vector<int> d(N, 0);
  d[0] = 0;

  if (N > 1) {
    d[1] = abs(f[1] - f[0]);
    for (int i = 2; i < N; ++i)
      d[i] = min(d[i-1] + abs(f[i] - f[i-1]), d[i-2] + abs(f[i] - f[i-2])*3);
  }

  os << d[N-1] << endl;
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
"3\n"
"1 5 10\n"
,
"9\n"
));
cases.push_back(make_pair(
"3\n"
"1 5 2\n"
,
"3\n"
));
cases.push_back(make_pair(
"1\n"
"100\n"
,
"0\n"
));
cases.push_back(make_pair(
"4\n"
"1 5 2 5\n"
,
"4\n"
));
cases.push_back(make_pair(
"2\n"
"1 100\n"
,
"99\n"
));

runner(cases, -1);
getchar();

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
solve(is, os);

#endif

}

