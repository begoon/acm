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
  for (int i = 0; i < (int)a.size(); ++i) {
    cerr << setw(2) << i << ": ";
    print(a[i]);
  }
  return cerr;
}

bool is_perfect(long long n) {
  if (n == 1) return false;
  long long s = 1;
  long long q = sqrt((double)n);
  for (long long i = 2; i <= q; ++i) {
    if ((n % i) == 0) {
      s += i;
      if (n/i != i) s += n/i;
    }
  }
  return s == n;
}

long long p[] = { 6, 28, 496, 8128, 33550336, 8589869056, 137438691328, 2305843008139952128 };

void solve(istream& is, ostream& os) {
  long long m, n;
  is >> m >> n >> ws;

  int N = sizeof(p) / sizeof(*p);
 
  bool found = false;
  int i;
  for (i = 0; i < N; ++i) {
    if (p[i] >= m && p[i] <= n) {
      os << p[i] << endl;
      found = true;
    }
  }
  if (!found) os << "Absent" << endl;
}


void solve_bruteforce(istream& is, ostream& os) {
  long long m, n;
  is >> m >> n >> ws;

  bool found = false;
  while (m <= n) {
    if (is_perfect(m)) {
      os << m << endl;
      found = true;
    }
    m += 1;
  }
  if (!found) os << "Absent" << endl;
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
    for (int i = 0; i < (int)cases.size(); ++i)
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
"6 6\n"
,
"6\n"
));

cases.push_back(make_pair(
"1 5000000000000000000\n"
,
"6\n"
"28\n"
"496\n"
"8128\n"
"33550336\n"
"8589869056\n"
"137438691328\n"
"2305843008139952128\n"
));


cases.push_back(make_pair(
"4 5\n"
,
"Absent\n"
));

cases.push_back(make_pair(
"5 30\n"
,
"6\n28\n"
));

cases.push_back(make_pair(
"6 6\n"
,
"6\n"
));

cases.push_back(make_pair(
"1 1\n"
,
"Absent\n"
));

runner(cases, -1);
getchar();

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
solve(is, os);

#endif

}