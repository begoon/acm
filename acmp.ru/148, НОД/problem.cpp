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

long long gcd(long long a, long long b)  {
  while (b != 0) {
    long long t = a % b;
    a = b;
    b = t;
  }
  return a;
}

void solve(istream& is, ostream& os) {
  long long a, b;
  is >> a >> b;
  os << gcd(a, b) << endl;
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
"12 42\n"
,
"6\n"
));

cases.push_back(make_pair(
"3 4\n"
,
"1\n"
));


runner(cases, -1);
getchar();

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
solve(is, os);

#endif

}

